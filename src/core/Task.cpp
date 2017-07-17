/*
 * Task.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/Task.h>

#include <QDebug>

namespace astviewer {

Task::Task() {
}

void Task::handleCommand(Command cmd) {
  using Command::CommandType;

  this->current = cmd;

  switch(cmd.t) {
  case CommandType::file_load:
    this->fileLoad();
    break;
  case CommandType::file_store:
    this->fileStore();
    break;
  case CommandType::query:
    this->commandInput();
    break;
  case CommandType::selection:
    this->sourceSelection();
    break;
  default:
    qDebug() << "Unsupported command type.";
    break;
  }
}

Task::~Task() {
}

} /* namespace astviewer */
