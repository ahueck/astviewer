/*
 * QLogHandler.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#include "util/QLogHandler.h"

#include <QDateTime>

namespace astviewer {

void QLogHandler::outputMessage(QtMsgType type,const QMessageLogContext &context, const QString &msg) {
  QString log_string;
  const auto time = QDateTime::currentDateTime().toString("hh:mm:ss");
  const auto format = tr("%0 %4: %1:%3 -> '%2'\n")
                          .arg(time,
                                context.function,
                                msg
                              )
                          .arg(context.line);
  switch (type) {
  case QtDebugMsg:
    log_string.append(format.arg("Debug"));
    break;
  case QtInfoMsg:
    log_string.append(format.arg("Info"));
    break;
  case QtWarningMsg:
    log_string.append(format.arg("Warning"));
    break;

  case QtCriticalMsg:
    log_string.append(format.arg("Critical"));
    break;
  case QtFatalMsg:
    log_string.append(format.arg("Fatal"));
    break;
  }

  emit doLog(log_string);
}

} /* namespace astviewer */
