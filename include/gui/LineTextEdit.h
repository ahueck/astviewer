/*
 * LineTextEdit.h
 *
 *  Created on: Aug 3, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_LINETEXTEDIT_H_
#define INCLUDE_GUI_LINETEXTEDIT_H_

#include <QObject>
#include <QPlainTextEdit>
#include <QSize>
#include <QWidget>

class QString;
class QPaintEvent;
class QRect;
class QResizeEvent;
class QWidget;

namespace astviewer {

namespace detail {
class LineNumberArea;
}

class LineTextEdit: public QPlainTextEdit {
Q_OBJECT
  friend class detail::LineNumberArea;
private:
  detail::LineNumberArea* number_area;
  bool show_current { true };

public:
  explicit LineTextEdit(QWidget* parent = nullptr);
  void showLine(bool);
  virtual ~LineTextEdit();

protected:
  void resizeEvent(QResizeEvent *event) override;

private slots:
  void updateLineNumberAreaWidth(int newBlockCount);
  void updateLineNumberArea(const QRect&, int);

private:
  void paintLineNumberEvent(QPaintEvent *event);
  int lineNumberAreaWidth();
};

namespace detail {
class LineNumberArea: public QWidget {
Q_OBJECT
private:
  LineTextEdit* editor;

public:
  explicit LineNumberArea(LineTextEdit* editor) :
      QWidget(editor), editor(editor) {
  }

  QSize sizeHint() const override {
    return QSize(editor->lineNumberAreaWidth(), 0);
  }

  virtual ~LineNumberArea() = default;

protected:
  void paintEvent(QPaintEvent *event) override {
    editor->paintLineNumberEvent(event);
  }
};
}

} /* namespace astviewer */

#endif /* INCLUDE_GUI_LINETEXTEDIT_H_ */
