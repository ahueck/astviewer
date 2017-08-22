/*
 * QueryApp.cpp
 *
 *  Created on: Jul 20, 2017
 *      Author: ahueck
 */

#include <QueryApp.h>
#include <clang/ClangToolSession.h>
#include <clang/QueryCompleterList.h>
#include <clang/QueryWrapper.h>
#include <core/DynamicCompleter.h>
#include <core/ToolWrapper.h>
#include <gui/CompletionInput.h>
#include <gui/Highlighter.h>
#include <gui/mainwindow.h>
#include <util/Util.h>

#include <QObject>

#include <algorithm>
#include <memory>

QueryApp::QueryApp() :
    CoreManager() {

}

void QueryApp::createInputWidget() {
  using namespace astviewer;
  auto* input = new CompletionInput();
  auto h = new Highlighter(input);
  input->setHighlighter(h);
  c = new DynamicCompleter(input);
  m = new QueryCompleterList(c);
  c->setDynModel(m);
  input->setCompleter(c);

  // CommandInput:
  QObject::connect(input, SIGNAL(commandEntered(QString)), this,
      SLOT(commandInput(QString)));
  QObject::connect(this, SIGNAL(fileLoadUnlock(bool)), input,
      SLOT(setEnabled(bool)));
  QObject::connect(this, SIGNAL(queryUnlock(bool)), input,
      SLOT(setEnabled(bool)));
  QObject::connect(this, SIGNAL(queryUnlock(bool)), input,
      SLOT(setEnabled(bool)));
  win->registerInput(input);
}

void QueryApp::createClangSession() {
  auto ctool = av::make_unique<av::QueryWrapper>();
  connect(ctool.get(), SIGNAL(sessionChanged(clang::query::QuerySession*)), m,
      SLOT(updateSession(clang::query::QuerySession*)));
  auto clang_tool = new av::ClangToolSession(std::move(ctool), this);
  this->clang_session = clang_tool;
  connect(clang_tool, SIGNAL(compilationDataBaseChanged(QStringList)), win,
      SLOT(updateDbView(QStringList)));
}

QueryApp::~QueryApp() = default;
