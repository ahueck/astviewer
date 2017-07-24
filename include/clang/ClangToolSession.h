/*
 * ClangToolSession.h
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_CLANGTOOLSESSION_H_
#define INCLUDE_CORE_CLANGTOOLSESSION_H_

#include <core/FutureTask.h>

#include <memory>
#include <vector>

namespace clang {
class ASTUnit;
namespace tooling {
class ClangTool;
class CompilationDatabase;
}
}

namespace astviewer {

class ToolWrapper;

class ClangToolSession: public FutureTask {
Q_OBJECT
private:
  std::unique_ptr<ToolWrapper> clang_tool;
  std::unique_ptr<clang::tooling::ClangTool> tool;
  std::unique_ptr<clang::tooling::CompilationDatabase> db;
  std::vector<std::unique_ptr<clang::ASTUnit>> AST_vec;

public:
  explicit ClangToolSession(std::unique_ptr<ToolWrapper> wrapper, QObject* parent = nullptr);
  ~ClangToolSession() override;

protected:
  void fileLoad(Command cmd) override;
  void commandInput(Command cmd) override;

private slots:
  void queryResult(Command matched_ast);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_CLANGTOOLSESSION_H_ */
