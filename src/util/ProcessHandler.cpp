/*
 * ProcessHandler.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#include <util/ProcessHandler.h>

#include <QAction>
#include <QStatusBar>
#include <QWidget>

namespace astviewer {

ProcessHandler::ProcessHandler(QObject* parent) :
    QObject(parent), spinner(nullptr, false, false) {
  spinner.setLineLength(5);
  spinner.setInnerRadius(5);
}

void ProcessHandler::setStatus(QStatusBar* status) {
  this->status = status;
  status->insertPermanentWidget(0, &spinner, 0);
}

void ProcessHandler::addWidget(QWidget* widget) {
  widgets.push_back(widget);
}

void ProcessHandler::addWidgets(std::initializer_list<QWidget*> widgets) {
  for (auto widget : widgets) {
    this->widgets.push_back(widget);
  }
}

void ProcessHandler::addAction(QAction* widget) {
  actions.push_back(widget);
}

void ProcessHandler::addActions(std::initializer_list<QAction*> actions) {
  for (auto action : actions) {
    this->actions.push_back(action);
  }
}

void ProcessHandler::clear() {
  widgets.clear();
  actions.clear();
}

void ProcessHandler::processStarted(QString msg) {
  for (auto widget : widgets) {
    widget->setEnabled(false);
  }
  for (auto action : actions) {
    action->setEnabled(false);
  }
  if (status) {
    spinner.start();
    status->showMessage(msg);
  }
}

void ProcessHandler::processFinished() {
  if (status) {
    status->clearMessage();
    spinner.stop();
  }
  for (auto widget : widgets) {
    widget->setEnabled(true);
  }
  for (auto action : actions) {
    action->setEnabled(true);
  }
}

ProcessHandler::~ProcessHandler() = default;

} /* namespace astviewer */
