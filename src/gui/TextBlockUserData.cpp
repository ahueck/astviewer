/*
 * TextBlockUserData.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: ahueck
 */

#include <gui/TextBlockUserData.h>

#include <QDebug>

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
      [&] (decltype(pos) position, Parenthesis::Type t, int& paren_index) {
        paren_index = 0;
        auto res =  std::find_if(std::begin(parens), std::end(parens), [&](const Parenthesis& p) {
              ++paren_index;
              return position == p.pos && t == p.t;
            });
        --paren_index;
        return res;
      };

  int index;
  auto iter = match(pos, Parenthesis::Type::Opened, index);
  if (iter != std::end(parens)) {
    qDebug() <<  "Match found";
    // match a closing bracket (forward)
    return matchOpenParenthesis(cursor, index);
  } else {
    iter = match(pos - 1, Parenthesis::Type::Closed, index);
    if (iter != std::end(parens)) {
      // match a opening bracket (backward)
    }
  }

  return TextBlockUserData::MatchType::NoMatch;
}

TextBlockUserData::MatchType TextBlockUserData::matchOpenParenthesis(
    QTextCursor& cursor, const int index_p) {
  auto block = cursor.block();
  auto user = userDataOf(block);
  auto parens = user->parentheses();
  auto closing_block = block;
  auto open_paren = parens.at(index_p);
  auto paren_pos = index_p + 1;


  qDebug() << "Finding bracket of idx: " << paren_pos << " end: " << parens.size();
  int depth = 0;
  while (true) {
    if (paren_pos >= parens.size()) {
      qDebug() <<  "Query new block";
      bool brackets_found = false;
      do {
        closing_block = closing_block.next();
        if (!closing_block.isValid()) {
          qDebug() <<  "Invalid block found";
          return TextBlockUserData::MatchType::NoMatch;
        }
        user = userDataOf(closing_block);
        brackets_found = user->hasParentheses();
      } while (!brackets_found);
      paren_pos = 0;
      parens = user->parentheses();
    }

    auto paren = parens.at(paren_pos);

    if (Parenthesis::Type::Opened == paren.t) {
      ++depth;
      qDebug() <<  "Analyze paren open" << depth;
    } else {
      qDebug() <<  "Analyze paren close" << depth;
      if (depth > 0) {
        --depth;
      } else {
        qDebug() <<  "Found paren close" << depth;
        cursor.clearSelection();
        cursor.setPosition(closing_block.position() + paren.pos + 1,
            QTextCursor::KeepAnchor);
        if (!Parenthesis::pair(open_paren, paren)) {
          qDebug() <<  "Not a pair - paren close" << depth;
          return TextBlockUserData::MatchType::Mismatch;
        }
        return TextBlockUserData::MatchType::Match;
      }
    }
    ++paren_pos;
  }

  return TextBlockUserData::MatchType::NoMatch;
}

TextBlockUserData::~TextBlockUserData() = default;

} /* namespace astviewer */
