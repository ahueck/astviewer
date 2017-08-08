/*
 * Highlighter.h
 *
 *  Created on: Aug 4, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_HIGHLIGHTER_H_
#define INCLUDE_GUI_HIGHLIGHTER_H_

#include <QSyntaxHighlighter>

namespace astviewer {

class Highlighter: public QSyntaxHighlighter {
public:
  Highlighter(QObject* parent = nullptr); // FIXME segfault when nullptr
  virtual void highlightBlock(const QString& text) override;
  virtual ~Highlighter();
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_HIGHLIGHTER_H_ */
