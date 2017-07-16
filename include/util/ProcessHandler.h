/*
 * ProcessHandler.h
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_PROCESSHANDLER_H_
#define INCLUDE_UTIL_PROCESSHANDLER_H_

#include <QObject>
#include <QList>
#include <QString>

#include <waitingspinnerwidget.h>

class QAction;
class QWidget;
class QStatusBar;

namespace astviewer {

class ProcessHandler: public QObject {
Q_OBJECT

private:
  WaitingSpinnerWidget spinner;
  QWidgetList widgets;
  QList<QAction*> actions;
  QStatusBar* status;

public:
  ProcessHandler(QObject* parent = 0);

  void setStatus(QStatusBar* status);

  void addWidget(QWidget* widget);

  void addWidgets(std::initializer_list<QWidget*> widgets);

  void addAction(QAction* widget);

  void addActions(std::initializer_list<QAction*> actions);

  void clear();

  virtual ~ProcessHandler();

public slots:
  void processStarted(QString msg);

  void processFinished();
};

} /* namespace astviewer */

#endif /* INCLUDE_UTIL_PROCESSHANDLER_H_ */
