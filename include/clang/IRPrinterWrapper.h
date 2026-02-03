/*
 * IRPrinterWrapper.h
 *
 *  Created on: Feb 1, 2026
 *      Author: ahueck
 */

#ifndef INCLUDE_CLANG_IRPRINTERWRAPPER_H_
#define INCLUDE_CLANG_IRPRINTERWRAPPER_H_

#include <core/ToolWrapper.h>

#include <llvm/Support/raw_ostream.h>

namespace irprinter {
class IRNodeFinder;
}  // namespace irprinter

namespace astviewer {

class IRPrinterWrapper : public ToolWrapper {
  std::string out_str;
  llvm::raw_string_ostream out{out_str};
  std::unique_ptr<irprinter::IRNodeFinder> irprinter;

 public:
  IRPrinterWrapper(QObject* parent = nullptr);
  void init(const CodeContext& data) override;
  void sourceSelection(Command cmd) override;
  virtual ~IRPrinterWrapper();
};

}  // namespace astviewer

#endif /* INCLUDE_CLANG_IRPRINTERWRAPPER_H_ */
