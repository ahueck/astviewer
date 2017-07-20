/*
 * CoreManager.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/CoreManager.h>
#include <core/Command.h>
#include <clang/ClangToolSession.h>
#include <gui/CommandInput.h>
#include <util/FileLoader.h>

#include <gui/mainwindow.h>

#include <QDebug>

namespace astviewer {

CoreManager::CoreManager(MainWindow* win, CommandInput* in,
    ClangToolSession* session) :
    tm(this), pm(this), win(win), input(in), session(session) {

  //pm.setStatus(win->getStatusbar());

  QObject::connect(this, SIGNAL(loadFile(Command)), &tm,
      SLOT(commitCommand(Command)));
  QObject::connect(this, SIGNAL(dispatchCommand(Command)), &tm,
      SLOT(commitCommand(Command)));
  QObject::connect(&tm, SIGNAL(taskDone(Command)), this,
      SLOT(handleFinished(Command)));
  //QObject::connect(this, SIGNAL(loadFile(Command)), this, SLOT(fileLoad()));

  // BUild file load Locking:
  /*
   auto& list = lockGroups["file_load"];
   list.push_back(QVariant(win->in));
   list.push_back(QVariant(win->ui->actionOpen_DB));
   */
  QObject::connect(this, SIGNAL(lockFileLoad(bool)), input,
      SLOT(setEnabled(bool)));
  //QObject::connect(this, SIGNAL(lockFileLoad(bool)), win->getUI()->actionOpen_DB, SLOT(setEnabled(bool)));
  //QObject::connect(this, SIGNAL(lockFileLoad(bool)), win->getUI()->actionOpen_File, SLOT(setEnabled(bool)));

  // Build query locking

  // Win & CommandInput:
  QObject::connect(win, SIGNAL(selectedTU(QString)), this,
      SLOT(selectedTU(QString)));
  QObject::connect(input, SIGNAL(commandEntered(QString)), this,
      SLOT(commandInput(QString)));
  //QObject::connect(win, SIGNAL(selectedCompilationDB(QString)), this, SLOT(selectedTU(QString)));

  f_loader = new FileLoader(this);
  QObject::connect(f_loader, SIGNAL(commandFinished(Command)), this,
      SLOT(sourceLoaded(Command)));
  tm.registerTask(f_loader);

  tm.registerTask(session);
  QObject::connect(session, SIGNAL(commandFinished(Command)), this,
      SLOT(clangResult(Command)));
}

void CoreManager::clangResult(Command cmd) {
  qDebug() << "Received clangResult";
  switch (cmd.t) {
  case Command::CommandType::query:
    win->setClangAST(cmd.result);
    break;
  default:
    qDebug() << "Not implemented";
    qDebug() << cmd.id << " " << cmd.input;
  }
}

void CoreManager::sourceLoaded(Command cmd) {
  win->setSource(cmd.result);
}

void CoreManager::handleFinished(Command cmd) {
  qDebug() << "Finished command: " << cmd.input;
  switch (cmd.t) {
  case Command::CommandType::file_load:
    emit lockFileLoad(true);
    break;
  case Command::CommandType::query:
    emit lockFileLoad(true);
    break;
  case Command::CommandType::selection:

    break;
  default:
    qDebug() << "Unsupported command type.";
    break; // or return;?
  }
  pm.processFinished(cmd.id);
}

void CoreManager::commandInput(QString input_str) {
  qDebug() << "Read command for processing: " << input_str;
  Command cmd;
  cmd.t = Command::CommandType::query;
  cmd.input = input_str;
  pm.processStarted(tr("Executing query: %0").arg(input_str), cmd.id);

  emit lockFileLoad(false);
  emit dispatchCommand(cmd);
}

void CoreManager::selectedCompilationDB(QString db_path) {
  qInfo() << "Not implemented";
}

void CoreManager::selectedTU(QString tu_path) {
  qDebug() << "TU received: " << tu_path;
  Command cmd;
  cmd.t = Command::CommandType::file_load;
  cmd.input = tu_path;

  pm.processStarted(tr("Loading file: %0").arg(tu_path), cmd.id);

  // lock loadGUI;
  /*
   auto& list = lockGroups["file_load"];
   for(auto& variant : list) {
   if(variant.canConvert<QWidget>()) {
   auto* widget = variant.value<QWidget*>();
   widget->setEnabled(false);
   } else if(variant.canConvert<QAction>()) {
   auto* widget = variant.value<QAction*>();
   widget->setEnabled(false);
   }
   }
   */
  emit lockFileLoad(false);
  emit loadFile(cmd);
}

CoreManager::~CoreManager() = default;

} /* namespace astviewer */
