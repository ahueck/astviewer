/*
 * QueryApp.cpp
 *
 *  Created on: Jul 20, 2017
 *      Author: ahueck
 */

#include <QueryApp.h>
#include <clang/ClangToolSession.h>
#include <clang/QueryWrapper.h>
#include <gui/mainwindow.h>
#include <util/Util.h>

#include <QStringList>

QueryApp::QueryApp() :
    CoreManager() {

}

void QueryApp::createClangSession() {
  std::unique_ptr<av::ToolWrapper> ctool = av::make_unique<av::QueryWrapper>();
  auto clang_tool = new av::ClangToolSession(std::move(ctool), this);
  this->clang_session = clang_tool;
  connect(clang_tool, SIGNAL(compilationDataBaseChanged(QStringList)), win,
      SLOT(updateDbView(QStringList)));
}

QueryApp::~QueryApp() = default;
