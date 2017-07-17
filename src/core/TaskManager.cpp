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

void TaskManager::selectedTU(QString tu_path) {
  Command cmd;
  auto id = cmd.id;
  this->command_tracker[id] = registered_task;
  cmd.input = tu_path;
  cmd.t = Command::CommandType::file_load;

  emit commandExecute(cmd);
}

void TaskManager::commandFinished(Command cmd) {
  auto value = --command_tracker[cmd.id];
  this->command_tracker[cmd.id] = value;
  if(value == 0) {
    using Command::CommandType;
    switch(cmd.t) {
    case CommandType::file_load:
      // unlock GUI for file load
      break;
    }
  }

}

TaskManager::~TaskManager() {

}

} /* namespace astviewer */
