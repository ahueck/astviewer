/*
 * CompilationDbDelegate.cpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ahueck
 */

#include <gui/CompilationDbDelegate.h>
#include <util/Util.h>

#include <QApplication>
#include <QFileInfo>
#include <QModelIndex>
#include <QStyle>
#include <QWidget>

namespace astviewer {

CompilationDbDelegate::CompilationDbDelegate(QObject* parent, int path_components)
    : QStyledItemDelegate(parent), path_components(path_components) {}

QString CompilationDbDelegate::displayText(const QVariant& value, const QLocale& locale) const {
  auto text = QStyledItemDelegate::displayText(value, locale);
  return shortenPath(text, path_components);
}

void CompilationDbDelegate::paint(QPainter* painter, const QStyleOptionViewItem& opt, const QModelIndex& index) const {
  if (index.data().canConvert<QString>()) {
    QStyleOptionViewItem option = opt;
    initStyleOption(&option, index);
    const QWidget* widget = option.widget;
    QStyle* style = widget ? widget->style() : QApplication::style();

    /*
     const auto elide = [&option](const QString& text) {
     return option.fontMetrics.elidedText(text,
     Qt::TextElideMode::ElideLeft, option.rect.width());
     };
     option.text = elide(option.text);
     */

    style->drawControl(QStyle::CE_ItemViewItem, &option, painter, widget);
  } else {
    QStyledItemDelegate::paint(painter, opt, index);
  }
}

CompilationDbDelegate::~CompilationDbDelegate() = default;

} /* namespace astviewer */
