/*
 * ToolWrapper.h
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_TOOLWRAPPER
#define INCLUDE_CORE_TOOLWRAPPER

#include <memory>
#include <string>
#include <vector>

#include <core/FutureTask.h>

#include <QObject>

namespace clang {
class ASTUnit;
namespace tooling {
class CompilationDatabase;
}  // namespace tooling
}  // namespace clang

namespace astviewer {

struct CodeContext {
  std::string file;
  std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec;
  const clang::tooling::CompilationDatabase& compilation_database;
};

class ToolWrapper : public FutureTask {
  Q_OBJECT

 public:
  explicit ToolWrapper(QObject* parent = nullptr);

  virtual void init(const CodeContext&) = 0;

  virtual ~ToolWrapper();
};

}  // namespace astviewer

#endif /* INCLUDE_CORE_TOOLWRAPPER */
