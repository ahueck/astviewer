/*
 * DynamicStringListModel.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: ahueck
 */

#include <core/DynamicStringListModel.h>

#include <QtDebug>

namespace astviewer {

DynamicStringListModel::DynamicStringListModel(QObject* parent) :QStringListModel(parent) {

}

void DynamicStringListModel::updateModelList(const QString& line, const QString& prefix, int cursor_pos) {
  emit modelUpdated(false);
}

DynamicStringListModel::~DynamicStringListModel() = default;

} /* namespace astviewer */
