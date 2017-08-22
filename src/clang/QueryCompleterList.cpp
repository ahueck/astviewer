/*
 * QueryCompleterList.cpp
 *
 *  Created on: Jul 31, 2017
 *      Author: ahueck
 */

#include <clang/QueryCompleterList.h>
#include <core/DynamicStringListModel.h>

#include <clang/clang-query/QueryParser.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/LineEditor/LineEditor.h>

#include <QString>
#include <QDebug>
#include <QStringList>

#include <string>

namespace astviewer {

QueryCompleterList::QueryCompleterList(QObject* parent) :
    DynamicStringListModel(parent) {

}

void QueryCompleterList::updateModelList(const QString& in_line,
    const QString& prefix, int cursor_pos) {
  if (wrapper == nullptr) {
    return;
  }
  qDebug() << "Completion with prefix: " << prefix << " and line: " << in_line
      << " at: " << cursor_pos << " line length: " << in_line.size();

  using namespace clang::query;
  std::string line = in_line.toStdString();
  llvm::StringRef line_ref(line);
  auto completions = QueryParser::complete(line_ref, cursor_pos, *wrapper);

  QStringList list;
  QStringList list_style;
  const auto completion_prefix = prefix.left(cursor_pos);
  for (auto& completion : completions) {
    list << completion_prefix + QString::fromStdString(completion.TypedText);
  }
  this->setStringList(list);
}

void QueryCompleterList::updateSession(clang::query::QuerySession* session) {
  qDebug() << "update query session";
  this->wrapper = session;
}

QueryCompleterList::~QueryCompleterList() = default;

} /* namespace astviewer */
