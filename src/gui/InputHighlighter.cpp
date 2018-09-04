/*
 * InputHighlighter.cpp
 *
 *  Created on: Sep 3, 2018
 *      Author: ahueck
 */

#include <gui/InputHighlighter.h>

#include <gui/TextBlockUserData.h>

namespace astviewer {

InputHighlighter::InputHighlighter(QObject* parent) : Highlighter(parent) {}

void InputHighlighter::highlightBlock(const QString& text) {
  Highlighter::highlightBlock(text);

  Parentheses block_parens;
  const auto length = text.length();
  for (int position = 0; position < length; ++position) {
    const auto c = text.at(position);
    if (Parenthesis::isOpened(c)) {
      block_parens.push_back(Parenthesis(Parenthesis::Type::Opened, c, position));
    } else if (Parenthesis::isClosed(c)) {
      block_parens.push_back(Parenthesis(Parenthesis::Type::Closed, c, position));
    }
  }
  auto u_data = userDataOf(currentBlock());
  u_data->setParentheses(block_parens);
}

InputHighlighter::~InputHighlighter() = default;

} /* namespace astviewer */
