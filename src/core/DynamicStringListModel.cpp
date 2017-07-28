/*
 * DynamicStringListModel.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: ahueck
 */

#include <core/DynamicStringListModel.h>

namespace astviewer {

DynamicStringListModel::DynamicStringListModel(QObject* parent) :QStringListModel(parent) {

}

void DynamicStringListModel::updateModelList(const QString& prefix) {
  emit modelUpdated(false);
}

DynamicStringListModel::~DynamicStringListModel() = default;

} /* namespace astviewer */
