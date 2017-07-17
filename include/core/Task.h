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
  Command current;
public:
  Task();
  virtual ~Task();
protected:
  virtual void fileLoad() { emitDone(); }
  virtual void fileStore() { emitDone(); }
  virtual void sourceSelection() { emitDone(); }
  virtual void commandInput() { emitDone(); }

  virtual void emitDone() {
    auto CMD = current;
    this->current = {};
    emit commandFinished(CMD);
  }

public slots:
  virtual void handleCommand(Command);
signals:
  void commandFinished(Command);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_TASK_H_ */
