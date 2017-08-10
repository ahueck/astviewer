/*
 * CommandInput.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#include <gui/CommandInput.h>

#include <gui/TextBlockUserData.h>

#include <QSyntaxHighlighter>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QWidget>

namespace astviewer {

CommandInput::CommandInput(QWidget* parent) :
    QTextEdit(parent) {
  //installEventFilter(this);
  QObject::connect(this, SIGNAL(commandEntered(QString)), this,
      SLOT(addToHistory(QString)));
  QObject::connect(this, SIGNAL(cursorPositionChanged()), this,
      SLOT(updateHighlights()));
}

void CommandInput::setHighlighter(QSyntaxHighlighter* h) {
  highlighter = h;
  if (highlighter) {
    highlighter->setParent(this);
    highlighter->setDocument(this->document());
  }
}

void CommandInput::updateHighlights() {
  QList<QTextEdit::ExtraSelection> paren_selection;

  auto cursor = textCursor();
  auto user = userDataOf(cursor.block());
  auto match = user->matchParenthesisCursor(cursor);

  switch (match) {
  case TextBlockUserData::MatchType::NoMatch: {
    qDebug() << "No matching brackets found";
    break;
  }
  case TextBlockUserData::MatchType::Match: [[fallthrough]]
  case TextBlockUserData::MatchType::Mismatch: {
    QTextEdit::ExtraSelection selection;

    qDebug() << "Applying format (" << cursor.selectionStart() << "/"
        << cursor.selectionEnd() << ") Mismatch: "
        << (TextBlockUserData::MatchType::Mismatch == match);

    selection.format.setBackground(Qt::lightGray);

    if(TextBlockUserData::MatchType::Mismatch == match) {
      selection.format.setFontStrikeOut(true);
    }

    selection.cursor = cursor;
    selection.cursor.clearSelection();
    selection.cursor.setPosition(cursor.selectionStart());
    selection.cursor.setPosition(selection.cursor.position() + 1,
        QTextCursor::KeepAnchor);
    paren_selection.push_back(selection);

    selection.cursor = cursor;
    selection.cursor.clearSelection();
    selection.cursor.setPosition(cursor.selectionEnd());
    selection.cursor.setPosition(selection.cursor.position() - 1,
        QTextCursor::KeepAnchor);
    paren_selection.push_back(selection);
    break;
  }
  default:
    qDebug() << "Unknown bracket matching result";
    return;
  }
  this->setExtraSelections(paren_selection);
}

void CommandInput::addToHistory(QString cmd) {
  qDebug() << "Add command to history: " << cmd;
}

void CommandInput::keyPressEvent(QKeyEvent* key) {
  switch (key->key()) {
  case Qt::Key_Enter:
  case Qt::Key_Return: {
    // TODO:
    // fetch line
    // emit line to ClangToolSession
    // put line as grey text one above a new command prompt
    qDebug() << "enter pressed";
    auto text = this->toPlainText();
    //this->clear();
    emit commandEntered(text);
    return;
  }
  case Qt::Key_Up:
    // TODO put history item to prompt
    break;
  case Qt::Key_Down:
    // TODO put history item to prompt
    break;
  }

  QTextEdit::keyPressEvent(key);
}

CommandInput::~CommandInput() = default;

} /* namespace astviewer */
