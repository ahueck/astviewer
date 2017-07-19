/*
 * TaskManager.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#include <core/TaskManager.h>

namespace astviewer {

TaskManager::TaskManager() {

}

void TaskManager::registerTask(Task* t) {
  // TODO register only for certain commands
  auto result = connect(this, SIGNAL(commandExecute(Command)), t, SLOT(handleCommand(Command)));
  connect(t, SIGNAL(commandFinished(Command)), this, SLOT(commandFinished(Command)));
  if(result) {
    ++registered_task;
  }
}

void TaskManager::deregisterTask(Task* t) {
  auto result = disconnect(this, SIGNAL(commandExecute(Command)), t, SLOT(handleCommand(Command)));
  disconnect(t, SIGNAL(commandFinished(Command)), this, SLOT(commandFinished(Command)));
  if(result) {
    --registered_task;
  }
}

void TaskManager::commitCommand(Command cmd) {
	auto id = cmd.id;
	this->command_tracker[id] = registered_task;

	emit commandExecute(cmd);
}

void TaskManager::commandFinished(Command cmd) {
  auto value = --command_tracker[cmd.id];
  this->command_tracker[cmd.id] = value;
  if(value == 0) {
    emit taskDone(cmd);
  }

}

TaskManager::~TaskManager() {

}

} /* namespace astviewer */
