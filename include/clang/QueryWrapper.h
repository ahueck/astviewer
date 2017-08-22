/*
 * QueryWrapper.h
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_QUERYWRAPPER_H_
#define INCLUDE_CORE_QUERYWRAPPER_H_

#include <core/ToolWrapper.h>

#include <QObject>

#include <memory>
#include <vector>

namespace astviewer {
class Command;
}  // namespace astviewer
namespace clang {
class ASTUnit;
}  // namespace clang

namespace clang {
namespace query {
class QuerySession;
}
}

namespace astviewer {

class QueryWrapper: public ToolWrapper {
Q_OBJECT

private:
  // TODO make QuerySession per command execution?
  std::unique_ptr<clang::query::QuerySession> qs;

public:
  explicit QueryWrapper(QObject* parent = nullptr);
  void init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) override;
  void commandInput(Command cmd) override;
  ~QueryWrapper() override;

protected slots:
  void futureFinished() override;

signals:
  void sessionChanged(clang::query::QuerySession*);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_QUERYWRAPPER_H_ */
