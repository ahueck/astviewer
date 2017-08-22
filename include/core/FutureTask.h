/*
 * FutureTask.h
 *
 *  Created on: Jul 24, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_FUTURETASK_H_
#define INCLUDE_CORE_FUTURETASK_H_

#include <core/Task.h>

#include <qtconcurrentrun.h>
#include <QDebug>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>
#include <QtConcurrent>

#include <algorithm>

namespace astviewer {

class Command;

class FutureTask: public Task {
Q_OBJECT
protected:
  QFutureWatcher<Command> cmd_watcher;

  template<typename F, typename ... Args>
  void run(F function, Args&&... arguments) {
    qDebug() << "Run Future";
    auto run = QtConcurrent::run(function, std::forward<Args>(arguments)...);
    cmd_watcher.setFuture(run);
  }

public:
  explicit FutureTask(QObject* parent = nullptr);
  virtual ~FutureTask();

protected slots:
  virtual void futureFinished();
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_FUTURETASK_H_ */
