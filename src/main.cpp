#include "Query.h"
#include "QueryParser.h"
#include "QuerySession.h"


#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/LineEditor/LineEditor.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Signals.h"
#include <fstream>
#include <string>

#include "gui/mainwindow.h"
#include "util/QLogHandler.h"
#include "core/ClangToolSession.h"
#include "gui/CommandInput.h"
#include <QApplication>
#include <QPointer>
#include <QDebug>

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::ast_matchers::dynamic;
using namespace clang::query;
using namespace clang::tooling;
using namespace llvm;

static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::OptionCategory ClangQueryCategory("clang-query options");

static cl::list<std::string> Commands("c", cl::desc("Specify command to run"),
                                      cl::value_desc("command"),
                                      cl::cat(ClangQueryCategory));

static cl::list<std::string> CommandFiles("f",
                                          cl::desc("Read commands from file"),
                                          cl::value_desc("file"),
                                          cl::cat(ClangQueryCategory));


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    using astviewer::QLogHandler;
    QLogHandler::instance()->outputMessage(type, context, msg);
}

int main(int argc, const char **argv) {
  llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);
/*
  CommonOptionsParser OptionsParser(argc, argv, ClangQueryCategory);

  if (!Commands.empty() && !CommandFiles.empty()) {
    llvm::errs() << argv[0] << ": cannot specify both -c and -f\n";
    return 1;
  }
  */
  /*
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  std::vector<std::unique_ptr<ASTUnit>> ASTs;
  if (Tool.buildASTs(ASTs) != 0)
    return 1;

  QuerySession QS(ASTs);

  if (!Commands.empty()) {
    for (auto I = Commands.begin(), E = Commands.end(); I != E; ++I) {
      QueryRef Q = QueryParser::parse(*I, QS);
      if (!Q->run(llvm::outs(), QS))
        return 1;
    }
  } else if (!CommandFiles.empty()) {
    for (auto I = CommandFiles.begin(), E = CommandFiles.end(); I != E; ++I) {
      std::ifstream Input(I->c_str());
      if (!Input.is_open()) {
        llvm::errs() << argv[0] << ": cannot open " << *I << "\n";
        return 1;
      }
      while (Input.good()) {
        std::string Line;
        std::getline(Input, Line);

        QueryRef Q = QueryParser::parse(Line, QS);
        if (!Q->run(llvm::outs(), QS))
          return 1;
      }
    }
  } else {
    LineEditor LE("clang-query");
    LE.setListCompleter([&QS](StringRef Line, size_t Pos) {
      return QueryParser::complete(Line, Pos, QS);
    });
    while (llvm::Optional<std::string> Line = LE.readLine()) {
      QueryRef Q = QueryParser::parse(*Line, QS);
      Q->run(llvm::outs(), QS);
      llvm::outs().flush();
      if (QS.Terminate)
        break;
    }
  }
  */
  using namespace astviewer;
  qInstallMessageHandler(myMessageOutput);
  QApplication a(argc, const_cast<char**>(argv));
  ClangToolSession session;
  CommandInput* inputWidget = new CommandInput();
  MainWindow w;
  w.registerInput(inputWidget);
  w.registerClangTool(&session);
  w.show();
  return a.exec();
}
