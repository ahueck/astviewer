#include <QueryApp.h>

#include <gui/mainwindow.h>
#include <gui/CommandInput.h>
#include <util/QLogHandler.h>

#include <QApplication>
#include <QDebug>

#include <clang/Tooling/CommonOptionsParser.h>
#include <llvm/Support/Signals.h>

// FIXME does not link properly without this:
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

void avLoggingOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    using astviewer::QLogHandler;
    QLogHandler::instance().outputMessage(type, context, msg);
}

int main(int argc, const char **argv) {
  namespace av = astviewer;
  llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);

  qInstallMessageHandler(avLoggingOutput);

  QApplication a(argc, const_cast<char**>(argv));

  QueryApp app;
  MainWindow w;
  av::CommandInput inputWidget;
  w.registerInput(&inputWidget);
  app.init(&w, &inputWidget);

  w.show();

  return a.exec();
}
