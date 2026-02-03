/*
 * LlvmIRHighlighter.h
 *
 *  Created on: Feb 2, 2026
 *      Author: ahueck
 */

#ifndef SRC_GUI_LLVMIRHIGHLIGHTER_H_
#define SRC_GUI_LLVMIRHIGHLIGHTER_H_

#include "Highlighter.h"

namespace astviewer {

class LlvmIRHighlighter : public Highlighter {
 public:
  LlvmIRHighlighter(QObject* parent);
  virtual void highlightBlock(const QString& text) override;
  virtual ~LlvmIRHighlighter();
};

} /* namespace astviewer */

#endif /* SRC_GUI_LLVMIRHIGHLIGHTER_H_ */
