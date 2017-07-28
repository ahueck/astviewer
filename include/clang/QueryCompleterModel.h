/*
 * QueryCompleterModel.h
 *
 *  Created on: Jul 27, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CLANG_CLANG_QUERY_QUERYCOMPLETERMODEL_H_
#define INCLUDE_CLANG_CLANG_QUERY_QUERYCOMPLETERMODEL_H_

#include <QCompleter>

#include <QDebug>
class QStringListModel;
#include <QStringListModel>

namespace astviewer {

class QueryCompleterModel: public QCompleter {
Q_OBJECT
public:
  int counter{0};
  QStringListModel* m;
  QueryCompleterModel(QObject* parent = nullptr);
  virtual ~QueryCompleterModel();

  QStringList splitPath(const QString &path) const
  {
    m->setStringList(m->stringList() << "hello");
      qDebug() << path;
      return QStringList();
  }

  QString pathFromIndex(const QModelIndex &index) const
  {
      // needed to use original value when value is selected
    qDebug() << index;
      return index.data().toString();
  }

  //void setCompletionPrefix(const QString &prefix);
};

} /* namespace astviewer */

#endif /* INCLUDE_CLANG_CLANG_QUERY_QUERYCOMPLETERMODEL_H_ */
