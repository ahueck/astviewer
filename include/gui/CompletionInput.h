/*
 * CompletionInput.h
 *
 *  Created on: Jul 26, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_COMPLETIONINPUT_H_
#define INCLUDE_GUI_COMPLETIONINPUT_H_

#include <gui/CommandInput.h>

#include <QObject>

class QAbstractItemModel;
class QCompleter;
class QKeyEvent;
class QString;
class QWidget;

namespace astviewer {

class DynamicCompleter;

class CompletionInput: public CommandInput {
Q_OBJECT

protected:
  DynamicCompleter* input_completer { nullptr };

public:
  explicit CompletionInput(QWidget* parent = nullptr);
  virtual ~CompletionInput();

protected:
  void keyPressEvent(QKeyEvent*) override;
  void completionEvent(QKeyEvent*, bool = false);

public slots:
  void setCompleter(DynamicCompleter*);

protected slots:
  void insertCompletion(const QString&);
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_COMPLETIONINPUT_H_ */
