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
  virtual void fileLoad(Command cmd) { emitDone(cmd); }
  virtual void fileStore(Command cmd) { emitDone(cmd); }
  virtual void sourceSelection(Command cmd) { emitDone(cmd); }
  virtual void commandInput(Command cmd) { emitDone(cmd); }

  virtual void emitDone(Command current) {
    // TODO Bookkeeping of commands in queue
    emit commandFinished(current);
  }

public slots:
  virtual void handleCommand(Command);
signals:
  void commandFinished(Command);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_TASK_H_ */
