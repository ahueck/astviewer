/*
 * ClangToolSession.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#include <clang/ClangToolSession.h>
#include <core/ToolWrapper.h>
#include <util/Util.h>

#include <QDebug>

#include <clang/Frontend/ASTUnit.h>
#include <clang/Tooling/Tooling.h>

#include <string>

namespace astviewer {

ClangToolSession::ClangToolSession(std::unique_ptr<ToolWrapper> wrapper,
    QObject* parent) :
    FutureTask(parent), clang_tool(std::move(wrapper)) {
  connect(clang_tool.get(), SIGNAL(commandFinished(Command)), this,
      SLOT(queryResult(Command)));
}

void ClangToolSession::fileLoad(Command cmd) {
  using clang::tooling::CompilationDatabase;
  using clang::tooling::ClangTool;
  const auto has =
      [](const std::vector<std::string>& files, std::string file) -> bool {
        auto pos = std::find(std::begin(files), std::end(files), file);
        return pos != std::end(files);
      };
  auto f = [&](Command cmd) -> Command {
    auto file = cmd.input;
    auto file_std = file.toStdString();
    StringRef file_ref(file_std);

    if(db == nullptr || !has(db->getAllFiles(), file_std)) {
      std::string er;
      db = CompilationDatabase::autoDetectFromSource(file_ref, er);
      if(db == nullptr || !er.empty()) {
        qDebug() << "Could not load compilation db of file: "
        << file
        << "Reason: " << QString::fromStdString(er);
        return cmd; // FIXME return failed command
    }
    reloaded_db = true;
  }
  llvm::ArrayRef<std::string> ref(file_std);
  tool = astviewer::make_unique<ClangTool>(*db.get(), ref);

  AST_vec.clear();
  tool->buildASTs(AST_vec);
  clang_tool->init(AST_vec);

  return cmd;
} ;
  run(f, cmd);
}

void ClangToolSession::commandInput(Command cmd) {
  qDebug() << "Received command: " << cmd.input;
  clang_tool->handleCommand(cmd);
  //emit matchedAST(this->query.run(in));
}

void ClangToolSession::queryResult(Command matched_ast) {
  qDebug() << "Query result received";
  emit commandFinished(matched_ast);
}

void ClangToolSession::futureFinished() {
  if (reloaded_db) {
    reloaded_db = false;
    QStringList files_list;
    auto files = db->getAllFiles();
    std::transform(std::begin(files), std::end(files),
        std::back_inserter(files_list), [](const std::string& s) {
          return QString::fromStdString(s);
        });
    emit compilationDataBaseChanged(files_list);
  }
  FutureTask::futureFinished();
}

ClangToolSession::~ClangToolSession() = default;

} /* namespace astviewer */
