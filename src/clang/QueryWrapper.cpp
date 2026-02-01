/*
 * QueryWrapper.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#include <clang/QueryWrapper.h>
#include <core/Command.h>
#include <core/ToolWrapper.h>
#include <util/Util.h>

#include <clang/clang-query/Query.h>
#include <clang/clang-query/QueryParser.h>
#include <clang/clang-query/QuerySession.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/IntrusiveRefCntPtr.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/raw_ostream.h>

#include <QDebug>

#include <string>

namespace astviewer {

using namespace clang::query;

QueryWrapper::QueryWrapper(QObject* parent) : ToolWrapper(parent), qs(nullptr) {}

void QueryWrapper::init(const CodeContext& data) {
  qDebug() << "Init tool. #ASTs: " << data.AST_vec.size();
  if (qs == nullptr) {
    qs = astviewer::make_unique<QuerySession>(data.AST_vec);
  } else {
    qs->ASTs = decltype(qs->ASTs)(data.AST_vec);
  }
  emit sessionChanged(qs.get());
}

void QueryWrapper::commandInput(Command cmd) {
  qDebug() << "Execute query request: " << cmd.input;
  // QuerySession& qsession = *qs.get();
  run([&](Command c) -> Command {
    auto file_std = c.input.toStdString();
    llvm::StringRef file_ref(file_std);

    QueryRef Q = QueryParser::parse(file_ref, *this->qs.get());

    std::string out_str;
    llvm::raw_string_ostream out(out_str);
    Q->run(out, *this->qs.get());

    c.result = QString::fromStdString(out.str());
    return c;
  }, cmd);
}

void QueryWrapper::futureFinished() {
  emit sessionChanged(qs.get());
  ToolWrapper::futureFinished();
}

QueryWrapper::~QueryWrapper() = default;

}  // namespace astviewer
