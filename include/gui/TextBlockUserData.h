/*
 * TextBlockUserData.h
 *
 *  Created on: Aug 7, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_TEXTBLOCKUSERDATA_H_
#define INCLUDE_GUI_TEXTBLOCKUSERDATA_H_

#include <QTextCursor>
#include <QTextBlock>
#include <QTextBlockUserData>

#include <QDebug>

namespace astviewer {

struct Parenthesis;
using Parentheses = QVector<Parenthesis>;

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

class TextBlockUserData;
inline TextBlockUserData* userDataOf(const QTextBlock& block);
inline void setParenthesesOf(const QTextBlock& block,
    const Parentheses& parens);
namespace detail {
template<typename Parenthesis::Type P_Type>
struct search;
}

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
  template<typename Parenthesis::Type P_Type>
  MatchType matchParenthesis(QTextCursor& cursor, const int parenthesis_index) {
    using Search_Trait = detail::search<P_Type>;
    const auto dir = Search_Trait::search_direction;

    auto candidate_block = cursor.block();
    auto user = userDataOf(candidate_block);
    auto paren_vec = user->parentheses();

    const auto p_to_match = std::next(std::begin(paren_vec), parenthesis_index);
    auto current_p = std::next(p_to_match, dir);

    auto depth { 0 };
    while (true) {
      if (Search_Trait::end(current_p, paren_vec)) {
        do {
          candidate_block = Search_Trait::next(candidate_block);
          if (!candidate_block.isValid()) {
            return TextBlockUserData::MatchType::NoMatch;
          }
          user = userDataOf(candidate_block);
        } while (!user->hasParentheses());
        paren_vec = user->parentheses();
        current_p = Search_Trait::start(paren_vec);
      }

      if (Search_Trait::Parenthesis_type == current_p->t) {
        ++depth;
      } else {
        if (depth > 0) {
          --depth;
        } else {
          cursor.clearSelection();
          cursor.setPosition(
              candidate_block.position() + current_p->pos
                  + Search_Trait::position_offset, QTextCursor::KeepAnchor);
          if (!Search_Trait::matches(*p_to_match, *current_p)) {
            return TextBlockUserData::MatchType::Mismatch;
          }
          return TextBlockUserData::MatchType::Match;
        }
      }
      std::advance(current_p, dir);
    }

    return TextBlockUserData::MatchType::NoMatch;
  }
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

namespace detail {

template<typename Parenthesis::Type P_Type>
struct search {
  static constexpr auto search_direction { 1 };
  static constexpr auto position_offset { 1 };
  static constexpr auto Parenthesis_type { P_Type };

  template<typename Iter_Elem, typename Container>
  inline static bool end(Iter_Elem&& e, Container&& vec) {
    return e == std::end(vec);
  }

  inline static QTextBlock next(const QTextBlock& block) {
    return block.next();
  }

  template<typename Container>
  inline static auto start(Container&& vec) -> decltype(std::begin(vec)) {
    return std::begin(vec);
  }

  inline static bool matches(const Parenthesis& to_match,
      const Parenthesis& current) {
    return Parenthesis::pair(to_match, current);
  }
};

template<>
struct search<Parenthesis::Type::Closed> {
  static constexpr auto search_direction { -1 };
  static constexpr auto position_offset { 0 };
  static constexpr auto Parenthesis_type { Parenthesis::Type::Closed };

  template<typename Iter_Elem, typename Container>
  inline static bool end(Iter_Elem&& e, Container&& vec) {
    return e == std::prev(std::begin(vec)); // Qt misses rend()
  }

  inline static QTextBlock next(const QTextBlock& block) {
    return block.previous();
  }

  template<typename Container>
  inline static auto start(
      Container&& vec) -> decltype(std::prev(std::end(vec))) {
    return std::prev(std::end(vec)); // Qt misses rbegin()
  }

  inline static bool matches(const Parenthesis& to_match,
      const Parenthesis& current) {
    return Parenthesis::pair(current, to_match);
  }
};

}

} /* namespace astviewer */

#endif /* INCLUDE_GUI_TEXTBLOCKUSERDATA_H_ */
