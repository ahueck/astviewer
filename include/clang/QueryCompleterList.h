/*
 * QueryCompleterList.h
 *
 *  Created on: Jul 31, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CLANG_QUERYCOMPLETERLIST_H_
#define INCLUDE_CLANG_QUERYCOMPLETERLIST_H_

#include <core/DynamicStringListModel.h>

namespace clang {
namespace query {
class QuerySession;
}
}

namespace astviewer {

class QueryCompleterList: public DynamicStringListModel {
Q_OBJECT
private:
  clang::query::QuerySession* wrapper { nullptr };
public:
  explicit QueryCompleterList(QObject* parent = nullptr);
  virtual ~QueryCompleterList();

public slots:
  void updateModelList(const QString& line, const QString& prefix, int cursor_pos) override;
  void updateSession(clang::query::QuerySession*);
};

} /* namespace astviewer */

#endif /* INCLUDE_CLANG_QUERYCOMPLETERLIST_H_ */
