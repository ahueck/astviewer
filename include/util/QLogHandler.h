/*
 * LogView.h
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_LOGVIEW_H_
#define INCLUDE_UTIL_LOGVIEW_H_

#include <QObject>
#include <QtCore>

class QString;
class QMessageLogContext;

namespace astviewer {

class QLogHandler: public QObject {
Q_OBJECT

private:
  QLogHandler() = default;

public:

  static QLogHandler& instance() {
    static QLogHandler logger;
    return logger;
  }

  void outputMessage(QtMsgType type, const QMessageLogContext &context,
      const QString &msg);

  ~QLogHandler() override = default;

signals:
  void doLog(const QString& message);

};

} /* namespace astviewer */

#endif /* INCLUDE_UTIL_LOGVIEW_H_ */
