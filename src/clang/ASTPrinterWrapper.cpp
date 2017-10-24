/*
 * ASTPrinterWrapper.cpp
 *
 *  Created on: Sep 19, 2017
 *      Author: ahueck
 */

#include <clang/ASTPrinterWrapper.h>
#include <util/Util.h>

#include <NodeFinder.h>
#include <ClangUtil.h>

namespace astviewer {

ASTPrinterWrapper::ASTPrinterWrapper(QObject* parent) : ToolWrapper(parent) {

}

void ASTPrinterWrapper::init(std::vector<std::unique_ptr<clang::ASTUnit>>& AST_vec) {
  qDebug() << "Init printer";
  auto& ctx = AST_vec[0]->getASTContext();
  astprinter = astviewer::make_unique<astprinter::NodeFinder>(ctx, out);
  astprinter->showColor(false);
}

void ASTPrinterWrapper::sourceSelection(Command cmd) {
  qDebug() << "Execute sourceSelection request: " << cmd.input;
  auto query = [&](Command c) -> Command {
    out_str.clear();
    astprinter->setLocation(c.row_start, c.row_end);
    astprinter->find(/*print_all_if_not_found=*/false);

    c.result = QString::fromStdString(out.str());

    return c;
  };
  run(query, cmd);
}

ASTPrinterWrapper::~ASTPrinterWrapper() = default;

} /* namespace astviewer */
