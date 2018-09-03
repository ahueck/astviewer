/*
 * Highlighter.cpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ahueck
 */

#include <gui/Highlighter.h>
#include <gui/TextBlockUserData.h>

#include <QRegularExpression>

namespace astviewer {

Highlighter::Highlighter(QObject* parent) : QSyntaxHighlighter(parent) {}

void Highlighter::highlightBlock(const QString& text) {
  static const QRegularExpression quote("['\"]([^ ']+[ ]*[^ ']*)+['\"]");
  static const QRegularExpression numbers("[0-9]+");
  static const QRegularExpression hex_numbers("0x[0-9a-fA-F]+");

  const auto apply_color = [&](QRegularExpressionMatchIterator& matches, const QColor& color) {
    while (matches.hasNext()) {
      const auto match = matches.next();
      setFormat(match.capturedStart(), match.capturedLength(), color);
    }
  };

  auto matches = numbers.globalMatch(text);
  apply_color(matches, Qt::darkCyan);

  matches = hex_numbers.globalMatch(text);
  apply_color(matches, Qt::darkCyan);

  matches = quote.globalMatch(text);
  apply_color(matches, Qt::darkGreen);
}

Highlighter::~Highlighter() = default;

} /* namespace astviewer */
