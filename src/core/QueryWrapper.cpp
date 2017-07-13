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

#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>
#include <QDebug>

namespace astviewer {

using namespace clang::tooling;
using namespace clang::query;

QueryWrapper::QueryWrapper(QObject* parent) : QObject(parent),  qs(nullptr), watcher(new QFutureWatcher<QString>(this)) {
  connect(&watcher, SIGNAL(finished()), this, SLOT(queryFinished()));
}

void QueryWrapper::createSession(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) {
  qs = std::unique_ptr<QuerySession>(new QuerySession(AST_vec));
}

void QueryWrapper::run(const QString& cmd) {
  // Not really threadsafe because "qs" is shared
  QuerySession& qsession = *qs.get();
  auto func = [cmd, &qsession]() -> QString {
    auto file_std = cmd.toStdString();
    StringRef file_ref(file_std);

    QueryRef Q = QueryParser::parse(file_ref, qsession);

    std::string out_str;
    llvm::raw_string_ostream out(out_str);
    Q->run(out, qsession);

    return QString::fromStdString(out.str());
  };
  QFuture<QString> run = QtConcurrent::run(func);
  watcher.setFuture(run);
}

void QueryWrapper::queryFinished() {
  auto result = watcher.future().result();
  qDebug() << "Query is finished";
  emit queryResult(result);
}

QueryWrapper::~QueryWrapper() {
}

} /* namespace astviewer */
