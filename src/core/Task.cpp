/*
 * Task.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/Task.h>

#include <QDebug>

namespace astviewer {

Task::Task(QObject* parent) :QObject(parent) {
}

void Task::handleCommand(Command cmd) {
  //this->current = cmd;

  switch(cmd.t) {
  case Command::CommandType::file_load:
    this->fileLoad(cmd);
    break;
  case Command::CommandType::file_store:
    this->fileStore(cmd);
    break;
  case Command::CommandType::query:
    this->commandInput(cmd);
    break;
  case Command::CommandType::selection:
    this->sourceSelection(cmd);
    break;
  default:
    qDebug() << "Unsupported command type.";
    break;
  }
}

Task::~Task() = default;

} /* namespace astviewer */
