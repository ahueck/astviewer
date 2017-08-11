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

Highlighter::Highlighter(QObject* parent) :
    QSyntaxHighlighter(parent) {

}

void Highlighter::highlightBlock(const QString& text) {
  static const QRegularExpression quote("\".*\"");

  auto matches = quote.globalMatch(text);
  while(matches.hasNext()) {
    const auto match = matches.next();
    setFormat(match.capturedStart(), match.capturedLength(), Qt::darkGreen);
  }

  Parentheses block_parens;
  const auto length = text.length();
  for (int position = 0; position < length; ++position) {
    const auto c = text.at(position);
    if(Parenthesis::isOpened(c)) {
      block_parens.push_back(Parenthesis(Parenthesis::Type::Opened, c, position));
    } else if(Parenthesis::isClosed(c)) {
      block_parens.push_back(Parenthesis(Parenthesis::Type::Closed, c, position));
    }
  }
  auto u_data = userDataOf(currentBlock());
  u_data->setParentheses(block_parens);
}

Highlighter::~Highlighter() = default;

} /* namespace astviewer */
