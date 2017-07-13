/*
 * LogView.h
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#ifndef SRC_GUI_LOGVIEW_H_
#define SRC_GUI_LOGVIEW_H_

#include <QObject>
#include <QPointer>

namespace astviewer {

class QLogHandler: public QObject {
  Q_OBJECT

private:
  QLogHandler() = default;

public:

  static QPointer<QLogHandler> instance() {
    static QPointer<QLogHandler> logger;
    if (!logger) {
      logger = new QLogHandler();
    }
    return logger;
  }

void outputMessage(QtMsgType type,const QMessageLogContext &context, const QString &msg);

virtual ~QLogHandler() = default;

signals:
void doLog(const QString& message);

};

} /* namespace astviewer */

#endif /* SRC_GUI_LOGVIEW_H_ */
