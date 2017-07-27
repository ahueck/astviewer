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

namespace astviewer {

CompletionInput::CompletionInput(QWidget* parent) :
    CommandInput(parent) {
  auto c = new QCompleter(this);
  QFileSystemModel* qm = new QFileSystemModel(this);
  qm->setRootPath(QDir::currentPath());
  QStringList l("has");
  l << "hasAncestor";
  l << "allOf";
  l << "anyOf";
  auto m = new QStringListModel(l, c);
  c->setModel(m);
  this->setCompleter(c);
}

void CompletionInput::completionEvent(QKeyEvent* e) {
  static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word

  QString completionPrefix = [&]() {
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText() + e->text(); // FIXME maybe buggy: e->text?
  }();

  if (completionPrefix != input_completer->completionPrefix()) {
    input_completer->setCompletionPrefix(completionPrefix);
    input_completer->popup()->setCurrentIndex(
        input_completer->completionModel()->index(0, 0));
  }

  QRect cr = cursorRect();
  cr.setWidth(
      input_completer->popup()->sizeHintForColumn(0)
          + input_completer->popup()->verticalScrollBar()->sizeHint().width());
  input_completer->complete(cr);
}

void CompletionInput::keyPressEvent(QKeyEvent* e) {
  if (input_completer) {
    const bool is_shortcut = ((e->modifiers() & Qt::ControlModifier)
        && e->key() == Qt::Key_Space);
    auto pop = input_completer->popup();

    if (!pop->isVisible()) {
      if (is_shortcut) {
        completionEvent(e);
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
    if(pop->isVisible() && input_completer->completionCount() == 1) {
      CommandInput::keyPressEvent(e);
      pop->clicked(pop->currentIndex());
      return;
    }
  }
  CommandInput::keyPressEvent(e);
}

void CompletionInput::updateCompleterModel(QAbstractItemModel* model) {
  if (input_completer != nullptr) {
    input_completer->setModel(model);
  }
}

void CompletionInput::setCompleter(QCompleter* c) {
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
  qDebug() << completion;
  qDebug() << input_completer->completionPrefix();
  QTextCursor tc = textCursor();
  int extra = completion.length()
      - input_completer->completionPrefix().length();
  qDebug() << extra;
  tc.movePosition(QTextCursor::Left);
  tc.movePosition(QTextCursor::EndOfWord);
  tc.insertText(completion.right(extra));
  qDebug() << completion.right(extra);
  setTextCursor(tc);
}

CompletionInput::~CompletionInput() = default;

} /* namespace astviewer */
