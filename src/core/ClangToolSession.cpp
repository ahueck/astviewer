/*
 * ClangToolSession.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#include "core/ClangToolSession.h"

#include "clang/Frontend/ASTUnit.h"
//#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include <QDebug>

namespace astviewer {

ClangToolSession::ClangToolSession() {

}

void ClangToolSession::loadTU(const QString& file) {
  using clang::tooling::CompilationDatabase;
  using clang::tooling::ClangTool;
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
  tool = std::unique_ptr<ClangTool>(new ClangTool(*db.get(), ref));

  tool->buildASTs(AST_vec);
  query.createSession(AST_vec);
  qDebug() << file;
}

void ClangToolSession::loadCompilationDB(const QString& file) {
  using clang::tooling::CompilationDatabase;
  qDebug() << "Loading Compilation DB ot supported!";
}

void ClangToolSession::commandInput(const QString& in) {
  qDebug() <<"Received command: " << in;
  emit matchedAST(this->query.run(in));
}

ClangToolSession::~ClangToolSession() {

}

} /* namespace astviewer */
