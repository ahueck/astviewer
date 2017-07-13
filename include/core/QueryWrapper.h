/*
 * QueryWrapper.h
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#ifndef SRC_CORE_QUERYWRAPPER_H_
#define SRC_CORE_QUERYWRAPPER_H_

#include <qobject.h>
#include <QString>
#include <qfuturewatcher.h>

#include <memory>

namespace clang {
class ASTUnit;
namespace query {
class QuerySession;
}
namespace tooling {
class ClangTool;
}
}

namespace astviewer {

class QueryWrapper : public QObject {
  Q_OBJECT

private:
  std::unique_ptr<clang::query::QuerySession> qs;
  QFutureWatcher<QString> watcher;

public:
  QueryWrapper(QObject* parent = 0);
  void createSession(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec);
  void run(const QString& command);
  virtual ~QueryWrapper();

private slots:
  void queryFinished();

signals:
  void queryResult(QString);
};

} /* namespace astviewer */

#endif /* SRC_CORE_QUERYWRAPPER_H_ */
