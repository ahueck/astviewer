/*
 * ClangToolSession.h
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#ifndef SRC_CORE_CLANGTOOLSESSION_H_
#define SRC_CORE_CLANGTOOLSESSION_H_


#include <QObject>

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

class ClangToolSession :public QObject {
Q_OBJECT
private:
  std::unique_ptr<ToolWrapper> clang_tool;
  std::unique_ptr<clang::tooling::ClangTool> tool;
  std::unique_ptr<clang::tooling::CompilationDatabase> db;
  std::vector<std::unique_ptr<clang::ASTUnit>> AST_vec;

public:
  ClangToolSession(std::unique_ptr<ToolWrapper> wrapper);
  ~ClangToolSession() override;

public slots:
  void loadTU(const QString&);
  void loadCompilationDB(const QString&);
  void commandInput(const QString&);

private slots:
  void queryResult(QString);
public:
signals:
  void matchedAST(const QString&);
  void inputCompletition(QStringList);

};

} /* namespace astviewer */

#endif /* SRC_CORE_CLANGTOOLSESSION_H_ */
