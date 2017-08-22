/*
 * Task.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/Task.h>
#include <core/Command.h>

#include <QDebug>

namespace astviewer {

Task::Task(QObject* parent) :
    QObject(parent) {
}

void Task::fileLoad(Command cmd) {
  emit commandSkipped(cmd);
}

void Task::fileStore(Command cmd) {
  emit commandSkipped(cmd);
}

void Task::sourceSelection(Command cmd) {
  emit commandSkipped(cmd);
}

void Task::commandInput(Command cmd) {
  emit commandSkipped(cmd);
}

void Task::compilationDb(Command cmd) {
  emit commandSkipped(cmd);
}

void Task::handleCommand(Command cmd) {
  //this->current = cmd;

  switch (cmd.t) {
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
  case Command::CommandType::compilationDb:
    this->compilationDb(cmd);
    break;
  default:
    qDebug() << "Unsupported command type.";
    emit commandSkipped(cmd);
    break;
  }
}

Task::~Task() = default;

} /* namespace astviewer */
