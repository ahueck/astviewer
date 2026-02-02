/*
 * ASTPrinterWrapper.cpp
 *
 *  Created on: Sep 19, 2017
 *      Author: ahueck
 */

#include <clang/ASTPrinterWrapper.h>
#include <util/Util.h>

#include <ClangUtil.h>
#include <NodeFinder.h>
#include "core/Command.h"

namespace astviewer {

ASTPrinterWrapper::ASTPrinterWrapper(QObject* parent) : ToolWrapper(parent) {}

void ASTPrinterWrapper::init(const CodeContext& data) {
  qDebug() << "Init printer";
  auto& ctx = data.AST_vec[0]->getASTContext();
  astprinter = astviewer::make_unique<astprinter::NodeFinder>(ctx, out);
  astprinter->showColor(false);
}

void ASTPrinterWrapper::sourceSelection(Command cmd) {
  if (cmd.t != Command::CommandType::selection) {
    return;
  }
  qDebug() << "Execute sourceSelection request: " << cmd;
  run(
      [&](Command c) -> Command {
        out_str.clear();
        astprinter->setLocation(c.row_start, c.row_end);
        astprinter->find(/*print_all_if_not_found=*/false);

        c.result = QString::fromStdString(out.str());

        return c;
      },
      cmd);
}

ASTPrinterWrapper::~ASTPrinterWrapper() = default;

}  // namespace astviewer
