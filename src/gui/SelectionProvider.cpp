/*
 * SelectionProvider.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: ahueck
 */

#include <gui/SelectionProvider.h>

#include <qplaintextedit.h>
#include <QTextBlock>
#include <QTextCursor>

namespace astviewer {

SelectionProvider::SelectionProvider(QObject* parent) :
    QObject(parent) {

}

void SelectionProvider::enableSelector(bool enable) {
  this->enabled = enable;
}

void SelectionProvider::installOn(QPlainTextEdit* edit) {
  this->edit = edit;
  edit->installEventFilter(this);
  edit->viewport()->installEventFilter(this);
}

bool SelectionProvider::eventFilter(QObject* watched, QEvent* event) {
  if (!enabled || event->type() != QEvent::MouseButtonRelease) {
    return QObject::eventFilter(watched, event);
  }

  auto cursor = edit->textCursor();
  if (!cursor.hasSelection()) {
    return QObject::eventFilter(watched, event);
  }

  const int start_c = cursor.selectionStart();
  const int end_c = cursor.selectionEnd();

  const auto line_count = [] (QTextCursor cursor) {
    unsigned lines {1u};
    cursor.movePosition(QTextCursor::StartOfLine);
    while (cursor.positionInBlock() > 0) {
      cursor.movePosition(QTextCursor::Up);
      ++lines;
    }
    auto block = cursor.block().previous();
    while(block.isValid()) {
      lines += block.lineCount();
      block = block.previous();
    }
    return lines;
  };

  cursor.setPosition(start_c);
  auto line_s = line_count(cursor);
  cursor.setPosition(end_c);
  auto line_e = line_count(cursor);

  if (line_s != start || line_e != end) {
    start = line_s;
    end = line_e;
    emit lineSelected(line_s, line_e);
  }
  return QObject::eventFilter(watched, event);
}

SelectionProvider::~SelectionProvider() = default;

} /* namespace astviewer */
