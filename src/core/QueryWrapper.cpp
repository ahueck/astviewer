/*
 * QueryWrapper.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#include "core/QueryWrapper.h"

#include "clang/Frontend/ASTUnit.h"
//#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "clang-query/Query.h"
#include "clang-query/QueryParser.h"
#include "clang-query/QuerySession.h"

namespace astviewer {

using namespace clang::tooling;
using namespace clang::query;

QueryWrapper::QueryWrapper() : qs(nullptr) {

}

void QueryWrapper::createSession(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) {
  qs = std::unique_ptr<QuerySession>(new QuerySession(AST_vec));
}

QString QueryWrapper::run(const QString& cmd) {
  auto file_std = cmd.toStdString();
  StringRef file_ref(file_std);

  QueryRef Q = QueryParser::parse(file_ref, *qs.get());

  std::string out_str;
  llvm::raw_string_ostream out(out_str);
  Q->run(out, *qs.get());

  return QString::fromStdString(out.str());
}

QueryWrapper::~QueryWrapper() {
  // TODO Auto-generated destructor stub
}

} /* namespace astviewer */
