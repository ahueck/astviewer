/*
 * ClangToolSession.h
 *
 *  Created on: Jul 11, 2017
 *      Author: ahueck
 */

#ifndef SRC_CORE_CLANGTOOLSESSION_H_
#define SRC_CORE_CLANGTOOLSESSION_H_

#include <core/QueryWrapper.h>

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

class ClangToolSession :public QObject {
Q_OBJECT
private:
  QueryWrapper query;
  std::unique_ptr<clang::tooling::ClangTool> tool;
  std::unique_ptr<clang::tooling::CompilationDatabase> db;
  std::vector<std::unique_ptr<clang::ASTUnit>> AST_vec;

public:
  ClangToolSession();
  virtual ~ClangToolSession();

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
