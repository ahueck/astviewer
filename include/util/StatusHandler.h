/*
 * StatusHandler.h
 *
 *  Created on: Jul 18, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_STATUSHANDLER_H_
#define INCLUDE_UTIL_STATUSHANDLER_H_

#include <QObject>
#include <QString>

class WaitingSpinnerWidget;
class QStatusBar;

namespace astviewer {

class StatusHandler: public QObject {
Q_OBJECT

private:
  WaitingSpinnerWidget* spinner;
  QStatusBar* status{nullptr};

public:
  StatusHandler(QObject* parent = nullptr);

  void setStatus(QStatusBar* status);

  ~StatusHandler() override;

public slots:
  void processStarted(QString msg, size_t id = 0);

  void processFinished(size_t id = 0);
};

} /* namespace astviewer */

#endif /* INCLUDE_UTIL_STATUSHANDLER_H_ */
