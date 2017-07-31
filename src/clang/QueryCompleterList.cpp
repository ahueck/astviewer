/*
 * QueryCompleterList.cpp
 *
 *  Created on: Jul 31, 2017
 *      Author: ahueck
 */

#include <clang/QueryCompleterList.h>

#include <clang/QueryWrapper.h>

#include <clang/clang-query/Query.h>
#include <clang/clang-query/QueryParser.h>
#include <clang/clang-query/QuerySession.h>

#include <QtDebug>

namespace astviewer {

QueryCompleterList::QueryCompleterList(QObject* parent) :
    DynamicStringListModel(parent) {

}

void QueryCompleterList::updateModelList(const QString& in_line, const QString& prefix, int cursor_pos) {
  if(wrapper == nullptr) {
    return;
  }
  qDebug() << "Completion with prefix: " << prefix << " and line: " << in_line << " at: " << cursor_pos;
  using namespace clang::query;
  std::string line = in_line.toStdString();
  llvm::StringRef line_ref(line);
  auto completions = QueryParser::complete(line_ref, line_ref.size(), *wrapper);
  QStringList list;
  for (auto& completion : completions) {
    list << prefix + QString::fromStdString(completion.TypedText);
  }
  qDebug() << "Candidates: " << list;
  this->setStringList(list);
}

void QueryCompleterList::updateSession(
    clang::query::QuerySession* session) {
  qDebug() << "update query session";
  this->wrapper = session;
}

QueryCompleterList::~QueryCompleterList() = default;

} /* namespace astviewer */
