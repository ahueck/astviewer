/*
 * CompletionInput.cpp
 *
 *  Created on: Jul 26, 2017
 *      Author: ahueck
 */

#include <gui/CompletionInput.h>

#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QStringListModel>
#include <QFileSystemModel>

//#include <clang/QueryCompleterModel.h>

#include <core/DynamicCompleter.h>

namespace astviewer {

CompletionInput::CompletionInput(QWidget* parent) :
    CommandInput(parent) {
}

void CompletionInput::completionEvent(QKeyEvent* e, bool filter) {
  static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word

  QString key_text = filter ? "" : e->text();

  QTextCursor tc = textCursor();
  QString completionPrefix = [&]() {
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText() + key_text; // FIXME maybe buggy: e->text?
    }();
  qDebug() << "Under cursor: " << completionPrefix;
  //if (completionPrefix != input_completer->completionPrefix()) {
  QString completionLine = [&]() {
    tc.select(QTextCursor::LineUnderCursor);
    return tc.selectedText() + key_text;
  }();
  qDebug() << "Line under cursor: " << completionLine;
  tc = textCursor();
  qDebug() << "Cursor data:" << tc.positionInBlock() << tc.position();
  input_completer->updateCompletion(completionLine, completionPrefix,
      tc.positionInBlock() + key_text.length());
  input_completer->popup()->setCurrentIndex(
      input_completer->completionModel()->index(0, 0));
  //}

  QRect cr = cursorRect();
  cr.setWidth(
      input_completer->popup()->sizeHintForColumn(0)
          + input_completer->popup()->verticalScrollBar()->sizeHint().width());
  input_completer->complete(cr);
}

void CompletionInput::keyPressEvent(QKeyEvent* e) {
  const bool is_shortcut = ((e->modifiers() & Qt::ControlModifier)
      && e->key() == Qt::Key_Space) || e->key() == Qt::Key_Tab;
  if (input_completer) {
    auto pop = input_completer->popup();

    if (!pop->isVisible()) {
      if (is_shortcut) {
        completionEvent(e, true);
      }
    } else {
      if (is_shortcut) {
        pop->hide();
        return;
      } else {
        switch (e->key()) {
        case Qt::Key_Return:
          pop->clicked(pop->currentIndex());
          return;
        }
        completionEvent(e);
      }
    }
    if (pop->isVisible() && input_completer->completionCount() == 1) {
      if (!is_shortcut) {
        CommandInput::keyPressEvent(e);
      }
      pop->clicked(pop->currentIndex());
      return;
    }
  }
  if (!is_shortcut) {
    CommandInput::keyPressEvent(e);
  }
}

void CompletionInput::setCompleter(DynamicCompleter* c) {
  if (c == nullptr) {
    return;
  }

  if (input_completer) {
    QObject::disconnect(input_completer, SIGNAL(activated(QString)), this,
        SLOT(insertCompletion(QString)));
  }

  input_completer = c;

  input_completer->setParent(this);
  input_completer->setWidget(this);
  input_completer->setCompletionMode(QCompleter::PopupCompletion);
  input_completer->setCaseSensitivity(Qt::CaseSensitive);
  input_completer->setWrapAround(false);
  input_completer->setFilterMode(Qt::MatchStartsWith);
  QObject::connect(input_completer, SIGNAL(activated(QString)), this,
      SLOT(insertCompletion(QString)));
}

void CompletionInput::insertCompletion(const QString& completion) {
  if (input_completer->widget() != this) {
    return;
  }
  qDebug() << "Insert completion with: " << completion;
  QTextCursor tc = textCursor();
  int extra = completion.length()
      - input_completer->completionPrefix().length();
  qDebug() << input_completer->completionPrefix() << " -> Extra: " << extra;
  //tc.movePosition(QTextCursor::Left);
  qDebug() << "Pos after left: " << tc.positionInBlock();
  //tc.movePosition(QTextCursor::EndOfWord);

  qDebug() << "To insert: " << completion.right(extra);
  tc.insertText(completion.right(extra));
  qDebug() << "Pos after insert: " << tc.positionInBlock();
  tc.movePosition(QTextCursor::EndOfWord);
  qDebug() << "Pos after end: " << tc.positionInBlock();
  setTextCursor(tc);
}

CompletionInput::~CompletionInput() = default;

} /* namespace astviewer */
