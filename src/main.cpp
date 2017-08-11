#include <QueryApp.h>

#include <gui/mainwindow.h>
#include <gui/CommandInput.h>
#include <gui/CompletionInput.h>
#include <util/QLogHandler.h>
#include <core/DynamicCompleter.h>
#include <core/DynamicStringListModel.h>

#include <clang/QueryCompleterList.h>

#include <QApplication>
#include <QDebug>

#include <clang/Tooling/CommonOptionsParser.h>
#include <llvm/Support/Signals.h>



// FIXME does not link properly without this:
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

void avLoggingOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    using astviewer::QLogHandler;
    QLogHandler::instance().outputMessage(type, context, msg);
}
#include <iostream>
int main(int argc, const char **argv) {
  namespace av = astviewer;
  llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);

  qInstallMessageHandler(avLoggingOutput);

  QApplication qapp(argc, const_cast<char**>(argv));

  QueryApp app;
  MainWindow w;;
  app.init(&w);

  w.show();

//  QApplication a(argc, const_cast<char**>(argv));
//  QList<QTextEdit::ExtraSelection> selections;
//  // create QTextEdit, with lot of text in it
//  QTextEdit w("Alice and Bob (and Eve). ");
//  for(int i=0;i<10;++i) w.setText(w.toPlainText() + w.toPlainText());
//
//  // prepare variables for highlights
//    QTextCharFormat fmt;
//    fmt.setUnderlineStyle(QTextCharFormat::SingleUnderline);
//    fmt.setUnderlineColor(Qt::red);
//  //fmt.setBackground(QBrush(QColor(230,230,230)));
//
//  // highlight all text in parenthesis
//  QTextCursor cursor = w.textCursor();
//  while( !(cursor = w.document()->find(QRegExp("\\([^)]*\\)"), cursor)).isNull()) {
//      QTextEdit::ExtraSelection sel = { cursor, fmt };
//      selections.append(sel);
//  }
//
//  // set, show, go!
//  w.setExtraSelections(selections);
//  w.show();
//  return a.exec();

  return qapp.exec();
}
