/*
 * InputHighlighter.h
 *
 *  Created on: Sep 3, 2018
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_INPUTHIGHLIGHTER_H_
#define INCLUDE_GUI_INPUTHIGHLIGHTER_H_

#include "Highlighter.h"

namespace astviewer {

class InputHighlighter : public Highlighter {
 public:
  InputHighlighter(QObject* parent);
  virtual void highlightBlock(const QString& text) override;
  virtual ~InputHighlighter();
};

} /* namespace astviewer */

#endif /* SRC_GUI_INPUTHIGHLIGHTER_H_ */
