/*
 * IRPrinterWrapper.cpp
 *
 *  Created on: Feb 1, 2026
 *      Author: ahueck
 */

#include <clang/IRPrinterWrapper.h>
#include <qdebug.h>
#include <qglobal.h>
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
#ifdef CLANG_RESOURCE_DIR
  irprinter->setOptFlag("-resource-dir=" CLANG_RESOURCE_DIR);
#endif
  irprinter->setOptFlag("-g");
  irprinter->setOptFlag("-fno-discard-value-names");
  irprinter->parse();
}

void IRPrinterWrapper::sourceSelection(Command cmd) {
  if (cmd.t != Command::CommandType::ir_selection) {
    return;
  }
  qDebug() << "Execute IR sourceSelection request: " << cmd;
  run(
      [&](Command c) -> Command {
        out_str.clear();
        if (irprinter) {
          // irprinter->...
          qDebug() << "Querying by location\n";
          irprinter->printByLocation(c.row_start, c.row_end);
        } else {
          out << "IRPrinter not initialized (requires CodeContext)\n";
        }

        c.result = QString::fromStdString(out.str());

        qDebug() << "IR Result size: " << c.result.size();

        return c;
      },
      cmd);
}

IRPrinterWrapper::~IRPrinterWrapper() = default;

}  // namespace astviewer
