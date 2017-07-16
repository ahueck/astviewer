/*
 * QueryWrapper.h
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#ifndef SRC_CORE_QUERYWRAPPER_H_
#define SRC_CORE_QUERYWRAPPER_H_

#include <core/ToolWrapper.h>

namespace clang {
namespace query {
class QuerySession;
}
}

namespace astviewer {

class QueryWrapper : public ToolWrapper {
  Q_OBJECT

private:
  // TODO make QuerySession per command execution?
  std::unique_ptr<clang::query::QuerySession> qs;

public:
  QueryWrapper(QObject* parent = 0);
  void init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) override;
  void execute(const QString& command) override;
  virtual ~QueryWrapper();
};

} /* namespace astviewer */

#endif /* SRC_CORE_QUERYWRAPPER_H_ */
