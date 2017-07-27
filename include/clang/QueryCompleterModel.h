/*
 * QueryCompleterModel.h
 *
 *  Created on: Jul 27, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CLANG_CLANG_QUERY_QUERYCOMPLETERMODEL_H_
#define INCLUDE_CLANG_CLANG_QUERY_QUERYCOMPLETERMODEL_H_

#include <QCompleter>

class QStringListModel;

namespace astviewer {

class QueryCompleterModel: public QCompleter {
Q_OBJECT
public:
  int counter{0};
  QStringListModel* m;
  QueryCompleterModel(QObject* parent = nullptr);
  virtual ~QueryCompleterModel();

  void setCompletionPrefix(const QString &prefix);
};

} /* namespace astviewer */

#endif /* INCLUDE_CLANG_CLANG_QUERY_QUERYCOMPLETERMODEL_H_ */
