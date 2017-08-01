/*
 * CommandInput.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#include <gui/CommandInput.h>

#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QStringListModel>

namespace astviewer {

CommandInput::CommandInput(QWidget* parent) :
    QTextEdit(parent) {
  //installEventFilter(this);
  QObject::connect(this, SIGNAL(commandEntered(QString)), this,
      SLOT(addToHistory(QString)));
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
