#include <core/ToolWrapper.h>
#include <core/QueryWrapper.h>
#include <core/ClangToolSession.h>
#include <gui/mainwindow.h>
#include <gui/CommandInput.h>
#include <util/QLogHandler.h>
#include <util/Util.h>

#include <QApplication>
#include <QPointer>
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

  std::unique_ptr<av::ToolWrapper> ctool = av::make_unique<av::QueryWrapper>();
  av::ClangToolSession session(std::move(ctool));

  auto* inputWidget = new av::CommandInput();

  MainWindow w;
  w.registerInput(inputWidget);
  w.registerClangTool(&session);
  w.show();

  return a.exec();
}
