/*
 * SelectionProvider.h
 *
 *  Created on: Oct 23, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_SELECTIONPROVIDER_H_
#define INCLUDE_GUI_SELECTIONPROVIDER_H_

#include <qobject.h>

class QPlainTextEdit;

namespace astviewer {

class SelectionProvider: public QObject {
Q_OBJECT
private:
  QPlainTextEdit* edit { nullptr };
  unsigned start { 0u };
  unsigned end { 0u };
  bool enabled { true };

public:
  SelectionProvider(QObject* parent);
  void installOn(QPlainTextEdit* edit);
  virtual ~SelectionProvider();
protected:
  bool eventFilter(QObject* watched, QEvent* event) override;

public slots:
  void enableSelector(bool);

signals:
  void lineSelected(unsigned, unsigned);
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_SELECTIONPROVIDER_H_ */
