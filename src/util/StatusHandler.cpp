/*
 * StatusHandler.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ahueck
 */

#include <util/StatusHandler.h>
#include <waitingspinnerwidget.h>

#include <QStatusBar>
#include <QTimer>

namespace astviewer {

StatusHandler::StatusHandler(QObject* parent) :
    QObject(parent) {
  spinner = new WaitingSpinnerWidget(nullptr, false, false);
  spinner->setLineLength(5);
  spinner->setInnerRadius(5);

  clearTimer = new QTimer(this);
  clearTimer->setSingleShot(true);
  connect(clearTimer, &QTimer::timeout, [this]() {
    if (status) {
      status->clearMessage();
    }
  });
}

void StatusHandler::setStatus(QStatusBar* status) {
  this->status = status;
  status->insertPermanentWidget(0, spinner, 0);
}

void StatusHandler::processStarted(QString msg, size_t id) {
  clearTimer->stop();
  ++activeTasks;
  if (status) {
    spinner->start();
    status->showMessage(msg);
  }
}

void StatusHandler::processFinished(size_t id) {
  if (activeTasks > 0) {
    --activeTasks;
  }
  if (activeTasks == 0) {
    spinner->stop();
    clearTimer->start(1000);
  }
}

StatusHandler::~StatusHandler() = default;

} /* namespace astviewer */
