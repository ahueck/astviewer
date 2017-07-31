#include <QueryApp.h>

#include <gui/mainwindow.h>
#include <gui/CommandInput.h>
#include <gui/CompletionInput.h>
#include <util/QLogHandler.h>
#include <core/DynamicCompleter.h>
#include <core/DynamicStringListModel.h>

#include <clang/QueryCompleterList.h>

#include <QApplication>
#include <QDebug>

#include <clang/Tooling/CommonOptionsParser.h>
#include <llvm/Support/Signals.h>

// FIXME does not link properly without this:
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    using astviewer::QLogHandler;
    QLogHandler::instance().outputMessage(type, context, msg);
}

int main(int argc, const char **argv) {
  namespace av = astviewer;
  llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);

  qInstallMessageHandler(myMessageOutput);

  QApplication a(argc, const_cast<char**>(argv));

  QueryApp app;
  MainWindow w;;
  app.init(&w);

  w.show();

  return a.exec();
}
