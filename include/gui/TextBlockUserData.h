/*
 * TextBlockUserData.h
 *
 *  Created on: Aug 7, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_TEXTBLOCKUSERDATA_H_
#define INCLUDE_GUI_TEXTBLOCKUSERDATA_H_

#include <qtextobject.h>

namespace astviewer {

struct Parenthesis {
  enum class Type
    : bool {
      Opened, Closed
  };

  Type t;
  QChar p;
  int pos;

  Parenthesis() :
      t(Type::Opened), p('('), pos(-1) {

  }
  Parenthesis(Type t, QChar c, int position) :
      t(t), p(c), pos(position) {
  }

  static bool isOpened(QChar c) {
    return c == '(' || c == '{' || c == '[';
  }

  static bool isClosed(QChar c) {
    return c == ')' || c == '}' || c == ']';
  }

  static bool pair(const Parenthesis& open, const Parenthesis& closed) {
    const auto o = open.p;
    const auto c = closed.p;
    if ((o == QLatin1Char('{') && c != QLatin1Char('}'))
        || (o == QLatin1Char('(') && c != QLatin1Char(')'))
        || (o == QLatin1Char('[') && c != QLatin1Char(']'))) {
      return false;
    }
    return true;
  }

};

using Parentheses = QVector<Parenthesis>;

class TextBlockUserData: public QTextBlockUserData {
private:
  Parentheses m_parentheses;

public:
  enum class MatchType
    : int {
      Match, Mismatch, NoMatch
  };
  TextBlockUserData();
  void setParentheses(const Parentheses &parentheses);
  void clearParentheses();
  const Parentheses &parentheses() const;
  bool hasParentheses() const;
  MatchType matchParenthesisCursor(QTextCursor& cursor);
  virtual ~TextBlockUserData();

protected:
  MatchType matchOpenParenthesis(QTextCursor& cursor, const int index_p);
};

inline TextBlockUserData* userDataOf(const QTextBlock& block) {
  TextBlockUserData* data = static_cast<TextBlockUserData*>(block.userData());
  if (!data && block.isValid()) {
    data = new TextBlockUserData();
    auto& c_block = const_cast<QTextBlock &>(block);
    c_block.setUserData(data);
  }
  return data;
}

inline void setParenthesesOf(const QTextBlock& block,
    const Parentheses& parens) {
  auto data = userDataOf(block);
  data->setParentheses(parens);
}

} /* namespace astviewer */

#endif /* INCLUDE_GUI_TEXTBLOCKUSERDATA_H_ */
