/*
 * QueryWrapper.h
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#ifndef SRC_CORE_QUERYWRAPPER_H_
#define SRC_CORE_QUERYWRAPPER_H_

#include <QString>

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

class QueryWrapper {
  std::unique_ptr<clang::query::QuerySession> qs;

public:
  QueryWrapper();
  void createSession(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec);
  QString run(const QString& command);
  virtual ~QueryWrapper();
};

} /* namespace astviewer */

#endif /* SRC_CORE_QUERYWRAPPER_H_ */
