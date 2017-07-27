/*
 * QueryCompleterModel.cpp
 *
 *  Created on: Jul 27, 2017
 *      Author: ahueck
 */

#include <clang/QueryCompleterModel.h>
#include <QStringList>
#include <QStringListModel>

#include <QDebug>
namespace astviewer {

QueryCompleterModel::QueryCompleterModel(QObject* parent) : QCompleter(parent) {
  QStringList l("has");
  l << "hasAncestor";
  l << "allOf";
  l << "anyOf";
  m = new QStringListModel(l, this);
  setModel(m);
}

void QueryCompleterModel::setCompletionPrefix(const QString &prefix) {
  qDebug() << prefix;
  QCompleter::setCompletionPrefix(prefix);
}

QueryCompleterModel::~QueryCompleterModel() = default;

} /* namespace astviewer */
