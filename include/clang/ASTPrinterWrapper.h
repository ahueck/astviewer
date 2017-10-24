/*
 * ASTPrinterWrapper.h
 *
 *  Created on: Sep 19, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CLANG_ASTPRINTERWRAPPER_H_
#define INCLUDE_CLANG_ASTPRINTERWRAPPER_H_

#include <core/ToolWrapper.h>

#include <llvm/Support/raw_ostream.h>

namespace astprinter {
class NodeFinder;
}

namespace astviewer {

class ASTPrinterWrapper: public ToolWrapper {
  std::string out_str;
  llvm::raw_string_ostream out{out_str};
  std::unique_ptr<astprinter::NodeFinder> astprinter;
public:
  ASTPrinterWrapper(QObject* parent = nullptr);
  void init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) override;
  void sourceSelection(Command cmd) override;
  virtual ~ASTPrinterWrapper();
};

} /* namespace astviewer */

#endif /* INCLUDE_CLANG_ASTPRINTERWRAPPER_H_ */
