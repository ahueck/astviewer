/*
 * ClangToolSession.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#include <core/ClangToolSession.h>
#include <core/ToolWrapper.h>
#include <core/QueryWrapper.h>
#include <util/Util.h>

#include <QDebug>

#include <clang/Frontend/ASTUnit.h>
#include <clang/Tooling/Tooling.h>

namespace astviewer {

ClangToolSession::ClangToolSession(std::unique_ptr<ToolWrapper> wrapper) : clang_tool(std::move(wrapper)) {
 connect(clang_tool.get(), SIGNAL(queryResult(Command)), this, SLOT(queryResult(Command)));
 connect(&loader, SIGNAL(finished()), this, SLOT(loadedTU()));
}

void ClangToolSession::fileLoad(Command cmd) {
  using clang::tooling::CompilationDatabase;
  using clang::tooling::ClangTool;

  auto f = [&]() {
    auto file = cmd.input;
    auto file_std = file.toStdString();
    StringRef file_ref(file_std);
    if(this->db == nullptr) {
      std::string er;
      db = CompilationDatabase::autoDetectFromSource(file_ref, er);
      if(db == nullptr || !er.empty()) {
        qDebug() << "Could not load compilation db of file: "
                  << file
                  << "Reason: " << QString::fromStdString(er);
        return;
      }
      // emit loaded CompDB
    }
    llvm::ArrayRef<std::string> ref(file_std);
    tool = astviewer::make_unique<ClangTool>(*db.get(), ref);

    tool->buildASTs(AST_vec);
    clang_tool->init(AST_vec);
  };

}

void ClangToolSession::commandInput(Command cmd) {
  qDebug() <<"Received command: " << cmd.input;
  clang_tool->execute(cmd);
  //emit matchedAST(this->query.run(in));
}

void ClangToolSession::queryResult(Command matched_ast) {
  qDebug() << "Query result received";
  emit commandFinished(matched_ast);
}

void ClangToolSession::loadedTU() {
  qDebug() << "Loaded TU";
  auto result = loader.future().result();
  emit commandFinished(result);
}

ClangToolSession::~ClangToolSession() = default;

} /* namespace astviewer */
