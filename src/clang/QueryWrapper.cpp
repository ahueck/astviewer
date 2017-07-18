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

namespace astviewer {

using namespace clang::query;

QueryWrapper::QueryWrapper(QObject* parent) : ToolWrapper(parent),  qs(nullptr) {

}

void QueryWrapper::init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) {
  qs = make_unique<QuerySession>(AST_vec);
}

void QueryWrapper::execute(Command cmd) {
  QuerySession& qsession = *qs.get();
  auto func = [cmd, &qsession]() -> Command {
    auto file_std = cmd.input;
    llvm::StringRef file_ref(file_std);

    QueryRef Q = QueryParser::parse(file_ref, qsession);

    std::string out_str;
    llvm::raw_string_ostream out(out_str);
    Q->run(out, qsession);
    cmd.result = QString::fromStdString(out.str());
    return cmd;
  };
  this->run(func);
}

QueryWrapper::~QueryWrapper() {
}

} /* namespace astviewer */
