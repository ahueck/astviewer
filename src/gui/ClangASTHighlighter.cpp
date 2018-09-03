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
  static const QRegularExpression expr("[A-Za-z]*(Expr|Operator|Literal) ");
  static const QRegularExpression pos("(col|line)[: ,a-o0-9]+[0-9]+");

  const auto apply_color = [&](QRegularExpressionMatchIterator& matches, const QColor& color) {
    while (matches.hasNext()) {
      const auto match = matches.next();
      setFormat(match.capturedStart(), match.capturedLength(), color);
    }
  };

  auto matches = decl.globalMatch(text);
  apply_color(matches, Qt::green);
  matches = stmt.globalMatch(text);
  apply_color(matches, Qt::yellow);
  matches = expr.globalMatch(text);
  apply_color(matches, Qt::darkYellow);
  matches = pos.globalMatch(text);
  apply_color(matches, Qt::red);
}

ClangASTHighlighter::~ClangASTHighlighter() = default;

} /* namespace astviewer */
