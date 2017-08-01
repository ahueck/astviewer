/*
 * CommandInput.h
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_COMMANDINPUT_H_
#define INCLUDE_GUI_COMMANDINPUT_H_

#include <QTextEdit>

class QCompleter;

namespace astviewer {

class CommandInput: public QTextEdit {
Q_OBJECT
public:
  explicit CommandInput(QWidget* parent = nullptr);
  //bool eventFilter(QObject *, QEvent *e) override;
  ~CommandInput() override;

protected:
  void keyPressEvent(QKeyEvent*) override;

public slots:
  //void commandFinished();
  void addToHistory(QString);

signals:
  void commandEntered(QString);
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_COMMANDINPUT_H_ */
