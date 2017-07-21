/*
 * QueryApp.cpp
 *
 *  Created on: Jul 20, 2017
 *      Author: ahueck
 */

#include <QueryApp.h>

#include <clang/ClangToolSession.h>
#include <clang/QueryWrapper.h>

#include <util/Util.h>

QueryApp::QueryApp() : CoreManager() {

}

void QueryApp::createClangSession() {
  std::unique_ptr<av::ToolWrapper> ctool = av::make_unique<av::QueryWrapper>();
  this->clang_session = new av::ClangToolSession(std::move(ctool), this);
}

QueryApp::~QueryApp() = default;
