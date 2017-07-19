/*
 * QLogHandler.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#include "util/QLogHandler.h"

#include <QDateTime>

#include <iostream>

namespace astviewer {

void QLogHandler::outputMessage(QtMsgType type,const QMessageLogContext &context, const QString &msg) {
  const auto time = QDateTime::currentDateTime().toString("hh:mm:ss");
  const auto format = tr("%0 %4: %1:%3 -> '%2'\n")
                          .arg(time,
                                context.function,
                                msg
                              )
                          .arg(context.line);
  QString msg_type = "";
  switch (type) {
  case QtDebugMsg:
    msg_type = "Debug";
    break;
  case QtInfoMsg:
    msg_type = "Info";
    break;
  case QtWarningMsg:
    msg_type = "Warning";
    break;
  case QtCriticalMsg:
    msg_type = "Critical";
    break;
  case QtFatalMsg:
    msg_type = "Fatal";
    break;
  }

  std::cerr << (format.arg(msg_type)).toStdString() << std::endl;
  //emit doLog(format.arg(msg_type));
}

} /* namespace astviewer */
