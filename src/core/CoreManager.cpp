/*
 * CoreManager.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/CoreManager.h>

namespace astviewer {

CoreManager::CoreManager(MainWindow* win) : tm(this), pm(this), win(win) {
  QObject::connect(this, SIGNAL(loadFile(Command)), &tm, SLOT(commandExecute(Command)));
  QObject::connect(&tm, SIGNAL(commandFinished(Command)), this, SLOT(handleFinished(Command)));
  //QObject::connect(this, SIGNAL(loadFile(Command)), this, SLOT(fileLoad()));

  // BUild file load Locking:
  /*
  auto& list = lockGroups["file_load"];
  list.push_back(QVariant(win->in));
  list.push_back(QVariant(win->ui->actionOpen_DB));
  */
  QObject::connect(this, SIGNAL(lockFileLoad(bool)), win->in, SLOT(setEnabled(bool)));
  QObject::connect(this, SIGNAL(lockFileLoad(bool)), win->ui->actionOpen_DB, SLOT(setEnabled(bool)));
  QObject::connect(this, SIGNAL(lockFileLoad(bool)), win->ui->actionOpen_File, SLOT(setEnabled(bool)));
}

void CoreManager::handleFinished(Command cmd) {
  using Command::CommandType;

  switch(cmd.t) {
  case CommandType::file_load:
    // unlock loadGUI;
    pm.processFinished(cmd.id);
    emit lockFileLoad(true);
    break;
  case CommandType::query:

    break;
  case CommandType::selection:

    break;
  default:
    qDebug() << "Unsupported command type.";
    break;
  }
}

void CoreManager::selectedTU(QString tu_path) {
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
