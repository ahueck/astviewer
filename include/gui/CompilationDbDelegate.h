/*
 * CompilationDbDelegate.h
 *
 *  Created on: Aug 1, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_COMPILATIONDBDELEGATE_H_
#define INCLUDE_GUI_COMPILATIONDBDELEGATE_H_

#include <QString>
#include <QStyledItemDelegate>

class QLocale;
class QModelIndex;
class QObject;
class QPainter;
class QStyleOptionViewItem;
class QVariant;

namespace astviewer {

class CompilationDbDelegate : public QStyledItemDelegate {
 private:
  int path_components;

 public:
  explicit CompilationDbDelegate(QObject* parent = nullptr, int path_components = 1);
  QString displayText(const QVariant& value, const QLocale& locale) const override;
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
  virtual ~CompilationDbDelegate();
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_COMPILATIONDBDELEGATE_H_ */
