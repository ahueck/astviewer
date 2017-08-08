/*
 * CommandInput.h
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_COMMANDINPUT_H_
#define INCLUDE_GUI_COMMANDINPUT_H_

#include <QTextEdit>

class QSyntaxHighlighter;

namespace astviewer {

class CommandInput: public QTextEdit {
Q_OBJECT
protected:
QSyntaxHighlighter* highlighter {nullptr};

public:
  CommandInput(QWidget* parent = nullptr);
  //bool eventFilter(QObject *, QEvent *e) override;
  void setHighlighter(QSyntaxHighlighter* h);
  ~CommandInput() override;

protected:
  void keyPressEvent(QKeyEvent*) override;

public slots:
  //void commandFinished();
  void addToHistory(QString);

protected slots:
  void updateHighlights();

signals:
  void commandEntered(QString);
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_COMMANDINPUT_H_ */
