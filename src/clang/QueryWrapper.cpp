/*
 * QueryWrapper.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#include <clang/QueryWrapper.h>

#include <util/Util.h>

#include <clang/clang-query/Query.h>
#include <clang/clang-query/QueryParser.h>
#include <clang/clang-query/QuerySession.h>

#include <clang/Frontend/ASTUnit.h>
#include <llvm/ADT/StringRef.h>

#include <QDebug>

namespace astviewer {

using namespace clang::query;

QueryWrapper::QueryWrapper(QObject* parent) : ToolWrapper(parent),  qs(nullptr) {

}

void QueryWrapper::init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) {
  qDebug() << "Init tool. #ASTs: " << AST_vec.size();
  if(qs == nullptr) {
    qs = make_unique<QuerySession>(AST_vec);
  } else {
    qs->ASTs = decltype(qs->ASTs)(AST_vec);
  }
}

void QueryWrapper::commandInput(Command cmd) {
  qDebug() << "Execute query request: " << cmd.input;
  //QuerySession& qsession = *qs.get();
  auto func = [&, cmd]() -> Command {
    Command c = cmd;
    auto file_std = c.input.toStdString();
    llvm::StringRef file_ref(file_std);

    QueryRef Q = QueryParser::parse(file_ref, *this->qs.get());

    std::string out_str;
    llvm::raw_string_ostream out(out_str);
    Q->run(out, *this->qs.get());

    c.result = QString::fromStdString(out.str());
    return c;
  };
  this->run(func);
}

QueryWrapper::~QueryWrapper() = default;

} /* namespace astviewer */


