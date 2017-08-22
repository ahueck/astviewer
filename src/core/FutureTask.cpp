/*
 * FutureTask.cpp
 *
 *  Created on: Jul 24, 2017
 *      Author: ahueck
 */

#include <core/FutureTask.h>
#include <core/Task.h>

#include <QFuture>

namespace astviewer {

FutureTask::FutureTask(QObject* parent) :
    Task(parent), cmd_watcher(this) {
  connect(&cmd_watcher, SIGNAL(finished()), this, SLOT(futureFinished()));
}

void FutureTask::futureFinished() {
  qDebug() << "Task is finished";
  auto result = cmd_watcher.future().result();
  emit commandFinished(result);
}

FutureTask::~FutureTask() = default;

} /* namespace astviewer */
