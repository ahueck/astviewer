/*
 * ClangASTHighlighter.h
 *
 *  Created on: Sep 3, 2018
 *      Author: ahueck
 */

#ifndef SRC_GUI_CLANGASTHIGHLIGHTER_H_
#define SRC_GUI_CLANGASTHIGHLIGHTER_H_

#include "Highlighter.h"

namespace astviewer {

class ClangASTHighlighter : public Highlighter {
 public:
  ClangASTHighlighter(QObject* parent);
  virtual void highlightBlock(const QString& text) override;
  virtual ~ClangASTHighlighter();
};

} /* namespace astviewer */

#endif /* SRC_GUI_CLANGASTHIGHLIGHTER_H_ */
