#include <QueryApp.h>

#include <gui/mainwindow.h>
#include <util/QLogHandler.h>

#include <QApplication>
#include <QDebug>

#include <clang/Tooling/CommonOptionsParser.h>

// FIXME does not link properly without this:
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

void avLoggingOutput(QtMsgType type, const QMessageLogContext &context,
    const QString &msg) {
  using astviewer::QLogHandler;
  QLogHandler::instance().outputMessage(type, context, msg);
}
#include <iostream>
int main(int argc, const char **argv) {
  namespace av = astviewer;
  //llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);

  qInstallMessageHandler(avLoggingOutput);

  QApplication qapp(argc, const_cast<char**>(argv));

  QueryApp app;
  MainWindow w;
  app.init(&w);

  w.show();

  return qapp.exec();
}
