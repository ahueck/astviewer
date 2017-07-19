/*
 * TaskManager.h
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_TASKMANAGER_H_
#define INCLUDE_CORE_TASKMANAGER_H_

#include <core/Command.h>

#include <QObject>
#include <QMap>

namespace astviewer {

class Task;

class TaskManager : public QObject {
Q_OBJECT

private:
  using cmd_counter = size_t;
  QMap<cmd_id, cmd_counter> command_tracker;
  size_t registered_task{0};

public:
  TaskManager();
  void registerTask(Task* t);
  void deregisterTask(Task* t);
  virtual ~TaskManager();

public slots:
  void commitCommand(Command);
  void commandFinished(Command);

signals:
  void commandExecute(Command);
  void taskDone(Command);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_TASKMANAGER_H_ */
