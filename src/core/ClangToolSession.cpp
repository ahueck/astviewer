/*
 * ClangToolSession.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#include <core/ClangToolSession.h>

#include <clang/Frontend/ASTUnit.h>
#include <clang/Tooling/Tooling.h>

#include <QDebug>

namespace astviewer {

ClangToolSession::ClangToolSession() : query(this) {
 connect(&query, SIGNAL(queryResult(QString)), this, SLOT(queryResult(QString)));
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
  query.init(AST_vec);
  qDebug() << file;
}

void ClangToolSession::loadCompilationDB(const QString& file) {
  using clang::tooling::CompilationDatabase;
  qDebug() << "Loading Compilation DB not supported!";
}

void ClangToolSession::commandInput(const QString& in) {
  qDebug() <<"Received command: " << in;
  this->query.execute(in);
  //emit matchedAST(this->query.run(in));
}

void ClangToolSession::queryResult(QString matched_ast) {
  qDebug() << "Query result received";
  emit matchedAST(matched_ast);
}

ClangToolSession::~ClangToolSession() {

}

} /* namespace astviewer */
