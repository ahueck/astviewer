/*
 * ClangToolSession.h
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_CLANGTOOLSESSION_H_
#define INCLUDE_CORE_CLANGTOOLSESSION_H_

#include <core/FutureTask.h>

#include <QObject>
#include <QString>

#include <memory>
#include <vector>

class QStringList;
namespace astviewer {
class Command;
}  // namespace astviewer

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
  std::vector<std::unique_ptr<ToolWrapper>> clang_tools;
  std::unique_ptr<clang::tooling::ClangTool> tool;
  std::unique_ptr<clang::tooling::CompilationDatabase> db;
  std::vector<std::unique_ptr<clang::ASTUnit>> AST_vec;
  bool reloaded_db { false };

public:
  explicit ClangToolSession(QObject* parent = nullptr);
  void addTool(std::unique_ptr<ToolWrapper> tool);
  ~ClangToolSession() override;

protected:
  void fileLoad(Command cmd) override;
  void commandInput(Command cmd) override;
  void sourceSelection(Command cmd) override;
  void compilationDb(Command cmd) override;
  void futureFinished() override;

private slots:
  void queryResult(Command matched_ast);
  void selectionResult(Command selection_ast);

signals:
  void compilationDataBaseChanged(QStringList);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_CLANGTOOLSESSION_H_ */
