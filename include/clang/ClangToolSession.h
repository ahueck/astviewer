/*
 * ClangToolSession.h
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_CLANGTOOLSESSION_H_
#define INCLUDE_CORE_CLANGTOOLSESSION_H_

#include <core/Task.h>

#include <QFutureWatcher>

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

class ClangToolSession: public Task {
Q_OBJECT
private:
  std::unique_ptr<ToolWrapper> clang_tool;
  std::unique_ptr<clang::tooling::ClangTool> tool;
  std::unique_ptr<clang::tooling::CompilationDatabase> db;
  std::vector<std::unique_ptr<clang::ASTUnit>> AST_vec;
  QFutureWatcher<Command> loader;

public:
  ClangToolSession(std::unique_ptr<ToolWrapper> wrapper);
  ~ClangToolSession() override;

protected:
  void fileLoad(Command cmd) override;
  void commandInput(Command cmd) override;

private slots:
  void queryResult(Command matched_ast);
  void loadedTU();
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_CLANGTOOLSESSION_H_ */
