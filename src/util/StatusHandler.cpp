/*
 * StatusHandler.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ahueck
 */

#include <util/StatusHandler.h>

#include <waitingspinnerwidget.h>

#include <QStatusBar>

namespace astviewer {

StatusHandler::StatusHandler(QObject* parent) :
    QObject(parent) {
  spinner = new WaitingSpinnerWidget(nullptr,false,false);
  spinner->setLineLength(5);
  spinner->setInnerRadius(5);
}

void StatusHandler::setStatus(QStatusBar* status) {
  this->status = status;
  status->insertPermanentWidget(0, spinner, 0);
}

void StatusHandler::processStarted(QString msg, size_t id) {
  if (status) {
    spinner->start();
    status->showMessage(msg);
  }
}

void StatusHandler::processFinished(size_t id) {
  if (status) {
    status->clearMessage();
    spinner->stop();
  }
}

StatusHandler::~StatusHandler() = default;

} /* namespace astviewer */
