/*
 * TaskManager.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/TaskManager.h>
#include <core/Task.h>

namespace astviewer {

TaskManager::TaskManager(QObject* parent) : QObject(parent) {

}

void TaskManager::registerTask(Task* t) {
  // TODO register only for certain commands
  auto result = true;
  /*auto result = */QObject::connect(this, SIGNAL(execute(Command)), t, SLOT(handleCommand(Command)));
    QObject::connect(t, SIGNAL(commandFinished(Command)), this, SLOT(finished(Command)));
    QObject::connect(t, SIGNAL(commandSkipped(Command)), this, SLOT(finished(Command)));
  if(result) {
    ++registered_task;
  }
}

void TaskManager::deregisterTask(Task* t) {
  auto result = true;
  /*auto result = */QObject::disconnect(this, SIGNAL(execute(Command)), t, SLOT(handleCommand(Command)));
  QObject::disconnect(t, SIGNAL(commandFinished(Command)), this, SLOT(finished(Command)));
  QObject::disconnect(t, SIGNAL(commandSkipped(Command)), this, SLOT(finished(Command)));
  if(result) {
    --registered_task;
  }
}

void TaskManager::commit(Command cmd) {
	auto id = cmd.id;
	this->command_tracker[id] = registered_task;

	emit execute(cmd);
}

void TaskManager::finished(Command cmd) {
  auto value = --command_tracker[cmd.id];
  this->command_tracker[cmd.id] = value;
  if(value == 0) {
    emit tasksFinished(cmd);
  }

}

TaskManager::~TaskManager() = default;

} /* namespace astviewer */
