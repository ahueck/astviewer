/*
 * TextBlockUserData.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: ahueck
 */

#include <gui/TextBlockUserData.h>

#include <QDebug>

#include <iterator>

namespace astviewer {

TextBlockUserData::TextBlockUserData() = default;

void TextBlockUserData::setParentheses(const Parentheses& parentheses) {
  m_parentheses = parentheses;
}

void TextBlockUserData::clearParentheses() {
  m_parentheses.clear();
}

const Parentheses& TextBlockUserData::parentheses() const {
  return m_parentheses;
}

bool TextBlockUserData::hasParentheses() const {
  return !m_parentheses.isEmpty();
}

TextBlockUserData::MatchType TextBlockUserData::matchParenthesisCursor(
    QTextCursor& cursor) {
  auto block = cursor.block();
  auto user = userDataOf(block);
  if (!user->hasParentheses()) {
    return TextBlockUserData::MatchType::NoMatch;
  }

  auto& parens = user->parentheses();
  const auto pos = cursor.position() - block.position();

  const auto match =
      [&] (decltype(pos) position, Parenthesis::Type t) {
        auto res = std::find_if(std::begin(parens), std::end(parens), [&](const Parenthesis& p) {
              return position == p.pos && t == p.t;
            });
        return res;
      };

  auto iter = match(pos, Parenthesis::Type::Opened);
  if (iter != std::end(parens)) {
    const auto pos = std::distance(std::begin(parens), iter);
    return matchParenthesis<Parenthesis::Type::Opened>(cursor, pos);
  } else {
    iter = match(pos - 1, Parenthesis::Type::Closed);
    if (iter != std::end(parens)) {
      const auto pos = std::distance(std::begin(parens), iter);
      return matchParenthesis<Parenthesis::Type::Closed>(cursor, pos);
    }
  }

  return TextBlockUserData::MatchType::NoMatch;
}

TextBlockUserData::~TextBlockUserData() = default;

} /* namespace astviewer */
