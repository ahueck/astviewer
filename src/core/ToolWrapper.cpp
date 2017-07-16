/*
 * ToolWrapper.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#include <core/ToolWrapper.h>

#include <QtConcurrent>
#include <QFuture>
#include <QObject>
#include <QDebug>

namespace astviewer {

ToolWrapper::ToolWrapper(QObject* parent) :
    QObject(parent) {
  connect(&watcher, SIGNAL(finished()), this, SLOT(queryFinished()));
}

void ToolWrapper::queryFinished() {
  qDebug() << "Query is finished";
  auto result = watcher.future().result();
  emit queryResult(result);
}

ToolWrapper::~ToolWrapper() = default;

} /* namespace astviewer */
