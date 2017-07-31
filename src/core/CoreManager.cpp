/*
 * CoreManager.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/CoreManager.h>
#include <core/Command.h>
#include <gui/CommandInput.h>
#include <util/FileLoader.h>

#include <gui/mainwindow.h>

#include <QDebug>

namespace astviewer {

CoreManager::CoreManager() :
    tm(this), pm(this) {
  QObject::connect(&tm, SIGNAL(tasksFinished(Command)), this,
      SLOT(handleFinished(Command)));
}

void CoreManager::init(MainWindow* win) {
  this->win = win;
  // Win:
  QObject::connect(win, SIGNAL(selectedTU(QString)), this,
      SLOT(selectedTU(QString)));
  QObject::connect(win, SIGNAL(selectedCompilationDB(QString)), this,
      SLOT(selectedCompilationDB(QString)));
  QObject::connect(win, SIGNAL(selectedDbListItem(QString)), this,
      SLOT(selectedTU(QString)));
  win->registerWithManager(this);
  pm.setStatus(win->getStatusbar());
  /*QObject::connect(win, SIGNAL(selectedCompilationDB(QString)), this,
   SLOT(selectedCompilationDB(QString)));*/

  createFileLoader();
  createInputWidget();
  createClangSession();
  connectFileLoader();
  connectClangSession();
  postInit();
}

void CoreManager::handleFinished(Command cmd) {
  qDebug() << "Finished command: " << cmd.input;
  switch (cmd.t) {
  case Command::CommandType::file_load:
    emit fileLoadUnlock(true);
    break;
  case Command::CommandType::query:
    emit queryUnlock(true);
    break;
  case Command::CommandType::selection:
    emit selectionUnlock(true);
    break;
  case Command::CommandType::compilationDb:
    emit fileLoadUnlock(true);
    break;
  default:
    qDebug() << "Unsupported command type.";
    break; // or return;?
  }
  pm.processFinished(cmd.id);
}

void CoreManager::createFileLoader() {
  f_loader = new FileLoader(this);
}

void CoreManager::connectFileLoader() {
  tm.registerTask(f_loader);
  QObject::connect(f_loader, SIGNAL(commandFinished(Command)), this,
      SLOT(sourceLoaded(Command)));
}

void CoreManager::connectClangSession() {
  tm.registerTask(clang_session);
  QObject::connect(clang_session, SIGNAL(commandFinished(Command)), this,
      SLOT(clangResult(Command)));
}

void CoreManager::clangResult(Command cmd) {
  qDebug() << "Received clangResult";
  switch (cmd.t) {
  case Command::CommandType::query:
    win->setClangAST(cmd.result);
    break;
  default:
    qDebug() << "Not implemented: " << cmd;
  }
}

void CoreManager::sourceLoaded(Command cmd) {
  qDebug() << "Finished file load: " << cmd.input;
  win->setSource(cmd.result);
  win->fileLoadFinished(cmd.input);
}

void CoreManager::commandInput(QString input_str) {
  qDebug() << "Read command for processing: " << input_str;
  Command cmd;
  cmd.t = Command::CommandType::query;
  cmd.input = input_str;

  pm.processStarted(tr("Executing query: %0").arg(input_str), cmd.id);

  emit queryUnlock(false);
  //emit dispatchCommand(cmd);
  qDebug() << "Commit command";
  tm.commit(cmd);
}

void CoreManager::selectedCompilationDB(QString db_path) {
  Command cmd;
  cmd.t = Command::CommandType::compilationDb;
  cmd.input = db_path;
  pm.processStarted(tr("Loading compile commands: %0").arg(db_path), cmd.id);

  emit fileLoadUnlock(false);
  //emit dispatchCommand(cmd);
  tm.commit(cmd);

}

void CoreManager::selectedTU(QString tu_path) {
  qDebug() << "TU received: " << tu_path;
  Command cmd;
  cmd.t = Command::CommandType::file_load;
  cmd.input = tu_path;

  pm.processStarted(tr("Loading file: %0").arg(tu_path), cmd.id);

  emit fileLoadUnlock(false);
  //emit dispatchCommand(cmd);
  tm.commit(cmd);
}

void CoreManager::postInit() {

}

CoreManager::~CoreManager() = default;

} /* namespace astviewer */
