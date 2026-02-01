/*
 * IRPrinterWrapper.cpp
 *
 *  Created on: Feb 1, 2026
 *      Author: ahueck
 */

#include <clang/IRPrinterWrapper.h>
#include <util/Util.h>

#include <printer/IRNodeFinder.h>

#include <QDebug>

namespace astviewer {

IRPrinterWrapper::IRPrinterWrapper(QObject* parent) : ToolWrapper(parent) {}

void IRPrinterWrapper::init(const CodeContext& data) {
  qDebug() << "Init IR printer";
  llvm::ArrayRef<std::string> ref(data.file);
  // FIXME: irprinter also needs argument adjuster to find the standard header includes..
  // Maybe implement this in irprinter via a cmake option @ LLVMTool.
  irprinter = astviewer::make_unique<irprinter::IRNodeFinder>(data.compilation_database, ref, out);
  irprinter->parse();
}

void IRPrinterWrapper::sourceSelection(Command cmd) {
  qDebug() << "Execute IR sourceSelection request: " << cmd.input;
  run([&](Command c) -> Command {
    out_str.clear();
    if (irprinter) {
      // irprinter->...
      irprinter->printByLocation(cmd.row_start, cmd.row_end);
    } else {
      out << "IRPrinter not initialized (requires CommonOptionsParser)\n";
    }

    c.result = QString::fromStdString(out.str());

    return c;
  }, cmd);
}

IRPrinterWrapper::~IRPrinterWrapper() = default;

}  // namespace astviewer
