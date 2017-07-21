/*
 * Task.h
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_TASK_H_
#define INCLUDE_CORE_TASK_H_

#include <core/Command.h>

#include <QObject>

namespace astviewer {

class Task : public QObject{
Q_OBJECT
private:
  // TODO: List of commands to handle
  // Command current;
public:
  Task(QObject* parent = nullptr);
  virtual ~Task();

protected:
  virtual void fileLoad(Command cmd);
  virtual void fileStore(Command cmd);
  virtual void sourceSelection(Command cmd);
  virtual void commandInput(Command cmd);

public slots:
  virtual void handleCommand(Command);
signals:
  void commandFinished(Command);
  void commandSkipped(Command);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_TASK_H_ */
