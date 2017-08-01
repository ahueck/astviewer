/*
 * CompilationDbDelegate.h
 *
 *  Created on: Aug 1, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_COMPILATIONDBDELEGATE_H_
#define INCLUDE_GUI_COMPILATIONDBDELEGATE_H_

#include <QStyledItemDelegate>
#include <QFileInfo>
namespace astviewer {

class CompilationDbDelegate : public QStyledItemDelegate {
public:
  CompilationDbDelegate(QObject* parent = nullptr);
  QString displayText(const QVariant &value, const QLocale& locale) const
  {
      //return d_func()->textForRole(Qt::DisplayRole, value, locale);
    auto text = QStyledItemDelegate::displayText(value, locale);
    return QFileInfo(text).fileName();
  }
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
  virtual ~CompilationDbDelegate();
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_COMPILATIONDBDELEGATE_H_ */
