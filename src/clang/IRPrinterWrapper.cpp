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

void IRPrinterWrapper::init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) {
  qDebug() << "Init IR printer";
  // FIXME: IRNodeFinder requires CommonOptionsParser.
}

void IRPrinterWrapper::sourceSelection(Command cmd) {
  qDebug() << "Execute IR sourceSelection request: " << cmd.input;
  auto query = [&](Command c) -> Command {
    out_str.clear();
    if (irprinter) {
      // irprinter->...
    } else {
      out << "IRPrinter not initialized (requires CommonOptionsParser)\n";
    }

    c.result = QString::fromStdString(out.str());

    return c;
  };
  run(query, cmd);
}

IRPrinterWrapper::~IRPrinterWrapper() = default;

} /* namespace astviewer */
