/*
 * LineTextEdit.cpp
 *
 *  Created on: Aug 3, 2017
 *      Author: ahueck
 */

#include <gui/LineTextEdit.h>

#include <QColor>
#include <QFontMetrics>
#include <QLatin1Char>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QRgb>
#include <QTextBlock>
#include <QTextCursor>

namespace astviewer {

LineTextEdit::LineTextEdit(QWidget* parent) :
    QPlainTextEdit(parent), number_area(new detail::LineNumberArea(this)) {
  connect(this, SIGNAL(blockCountChanged(int)), this,
      SLOT(updateLineNumberAreaWidth(int)));
  connect(this, SIGNAL(updateRequest(QRect,int)), this,
      SLOT(updateLineNumberArea(QRect,int)));

  updateLineNumberAreaWidth(0);
}

void LineTextEdit::showLine(bool show) {
  show_current = show;
}

void LineTextEdit::updateLineNumberAreaWidth(int /* newBlockCount */) {
  setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void LineTextEdit::updateLineNumberArea(const QRect &rect, int dy) {
  if (dy != 0) {
    number_area->scroll(0, dy);
  } else {
    number_area->update(0, rect.y(), number_area->width(), rect.height());
  }

  if (rect.contains(viewport()->rect())) {
    updateLineNumberAreaWidth(0);
  }
}

void LineTextEdit::resizeEvent(QResizeEvent *e) {
  QPlainTextEdit::resizeEvent(e);

  QRect cr = contentsRect();
  number_area->setGeometry(
      QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void LineTextEdit::paintLineNumberEvent(QPaintEvent* event) {
  QPainter painter(number_area);
  painter.fillRect(event->rect(), QColor(qRgb(180, 180, 180)));

  QTextBlock block = firstVisibleBlock();
  int blockNumber = block.blockNumber();
  int top = static_cast<int>(blockBoundingGeometry(block).translated(
      contentOffset()).top());
  int bottom = top + static_cast<int>(blockBoundingRect(block).height());

  const auto cursor_block = textCursor().block();

  while (block.isValid() && top <= event->rect().bottom()) {
    if (block.isVisible() && bottom >= event->rect().top()) {
      if (block == cursor_block && show_current) {
        painter.fillRect(0, top, number_area->width(), fontMetrics().height(),
            QColor(qRgb(120, 120, 120)));
      }
      QString number = QString::number(blockNumber + 1);
      painter.setPen(QColor(qRgb(245, 245, 245)));
      painter.drawText(0, top, number_area->width(), fontMetrics().height(),
          Qt::AlignRight, number);
    }

    block = block.next();
    top = bottom;
    bottom = top + static_cast<int>(blockBoundingRect(block).height());
    ++blockNumber;
  }
}

int LineTextEdit::lineNumberAreaWidth() {
  int num_blocks = qMax(1, blockCount());
  const int digits =
      (num_blocks < 10 ?
          1 :
          (num_blocks < 100 ?
              2 :
              (num_blocks < 1000 ?
                  3 :
                  (num_blocks < 10000 ?
                      4 :
                      (num_blocks < 100000 ?
                          5 :
                          (num_blocks < 1000000 ?
                              6 :
                              (num_blocks < 10000000 ?
                                  7 :
                                  (num_blocks < 100000000 ?
                                      8 : (num_blocks < 1000000000 ? 9 : 10)))))))));

  return 3 + fontMetrics().width(QLatin1Char('9')) * digits;
}

LineTextEdit::~LineTextEdit() = default;

} /* namespace astviewer */
