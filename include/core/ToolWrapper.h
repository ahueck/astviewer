/*
 * ToolWrapper.h
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_TOOLWRAPPER_H_
#define INCLUDE_CORE_TOOLWRAPPER_H_

#include <core/Command.h>

#include <QtConcurrent>
#include <QFutureWatcher>
#include <QObject>
#include <QString>

#include <QDebug>

#include <memory>

namespace clang {
class ASTUnit;
}

namespace astviewer {

class ToolWrapper: public QObject {
Q_OBJECT

protected:
  QFutureWatcher<Command> watcher;

  template<typename F>
  void run(F function) {
    QFuture<Command> run = QtConcurrent::run(function);
    watcher.setFuture(run);
  }

public:
  ToolWrapper(QObject* parent = nullptr);

  virtual void init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) = 0;
  virtual void execute(Command command) = 0;

  ~ToolWrapper() override;

signals:
  void queryResult(Command);

protected slots:
  virtual void queryFinished();

};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_TOOLWRAPPER_H_ */
