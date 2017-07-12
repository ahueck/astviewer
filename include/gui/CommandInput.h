/*
 * CommandInput.h
 *
 *  Created on: Jul 12, 2017
 *      Author: ahueck
 */

#ifndef SRC_GUI_COMMANDINPUT_H_
#define SRC_GUI_COMMANDINPUT_H_

#include <qtextedit.h>

namespace astviewer {

class CommandInput: public QTextEdit {
  Q_OBJECT
public:
  CommandInput(QWidget* parent = 0);
  bool eventFilter(QObject *, QEvent *e) override;
  virtual ~CommandInput();

public slots:
  void addToHistory(const QString&);

signals:
  void commandEntered(const QString&);
};

} /* namespace astviewer */

#endif /* SRC_GUI_COMMANDINPUT_H_ */
