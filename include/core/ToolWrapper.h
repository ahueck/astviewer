/*
 * ToolWrapper.h
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_TOOLWRAPPER_H_
#define INCLUDE_CORE_TOOLWRAPPER_H_

#include <core/Command.h>
#include <core/FutureTask.h>

#include <QObject>

#include <memory>

namespace clang {
class ASTUnit;
}

namespace astviewer {

class ToolWrapper: public FutureTask {
Q_OBJECT

public:
  explicit ToolWrapper(QObject* parent = nullptr);

  virtual void init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) = 0;

  virtual ~ToolWrapper();
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_TOOLWRAPPER_H_ */
