/*
 * ClangASTHighlighter.cpp
 *
 *  Created on: Sep 3, 2018
 *      Author: ahueck
 */

#include <gui/ClangASTHighlighter.h>

#include <QRegularExpression>

namespace astviewer {

ClangASTHighlighter::ClangASTHighlighter(QObject* parent) : Highlighter(parent) {}

void ClangASTHighlighter::highlightBlock(const QString& text) {
  Highlighter::highlightBlock(text);

  static const QRegularExpression decl("[A-Za-z]*Decl ");
  static const QRegularExpression stmt("[A-Za-z]*Stmt ");
  static const QRegularExpression expr("[A-Za-z]*(Expr|Operator|Literal|ExprWithCleanups) ");
  static const QRegularExpression pos("(col|line)[: ,a-o0-9]+[0-9]+");
  static const QRegularExpression path("(\\/\\w+)+\\.\\w+([:0-9]+)");
  static const QRegularExpression nullr("<<<NULL>>>");

  const auto apply_color = [&](QRegularExpressionMatchIterator& matches, const QColor& color) {
    while (matches.hasNext()) {
      const auto match = matches.next();
      setFormat(match.capturedStart(), match.capturedLength(), color);
    }
  };

  auto matches = decl.globalMatch(text);
  apply_color(matches, {"#e06c3a"});  //#1390c2
  matches = stmt.globalMatch(text);
  apply_color(matches, {"#5691f3"});  // TODO improve color
  matches = expr.globalMatch(text);
  apply_color(matches, {"#1290c3"});
  matches = pos.globalMatch(text);
  apply_color(matches, {"#138c5a"});
  matches = path.globalMatch(text);
  apply_color(matches, Qt::darkGray);
  matches = nullr.globalMatch(text);
  apply_color(matches, Qt::gray);
}

ClangASTHighlighter::~ClangASTHighlighter() = default;

} /* namespace astviewer */
