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

namespace astviewer {

CommandInput::CommandInput(QWidget* parent) : QTextEdit(parent) {
  installEventFilter(this);
  QObject::connect(this, SIGNAL(commandEntered(QString)), this, SLOT(addToHistory(QString)));
}

void CommandInput::addToHistory(QString cmd) {
  qDebug() << "Add command to history: " << cmd;
}

bool CommandInput::eventFilter(QObject* obj, QEvent* e) {
  auto type = e->type();
  if(QEvent::KeyPress != type) {
    return QObject::eventFilter(obj, e);;
  }
  auto key_event = static_cast<QKeyEvent*>(e);
  auto key = key_event->key();
  switch(key) {
  case Qt::Key_Enter:
  case Qt::Key_Return:
  {
    // TODO:
    // fetch line
    // emit line to ClangToolSession
    // put line as grey text one above a new command prompt
    qDebug() << "enter pressed";
    auto text = this->toPlainText();
    //this->clear();
    emit commandEntered(text);

    return true;
  }
  case Qt::Key_Up:
    // TODO put history item to prompt
    break;
  case Qt::Key_Down:
    // TODO put history item to prompt
    break;
  }

  return QObject::eventFilter(obj, e);
}

CommandInput::~CommandInput() = default;

} /* namespace astviewer */
