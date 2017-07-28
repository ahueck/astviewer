/*
 * DynamicCompleter.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: ahueck
 */

#include <core/DynamicCompleter.h>

#include <QString>

namespace astviewer {

DynamicCompleter::DynamicCompleter(QObject* parent) : QCompleter(parent) {

}

void DynamicCompleter::setDynModel(DynamicStringListModel* m) {
  this->dyn_model = m;
  this->setModel(m);
}

void DynamicCompleter::updateCompletion(const QString& prefix) {
  dyn_model->updateModelList(prefix);
  QCompleter::setCompletionPrefix(prefix);
}

DynamicCompleter::~DynamicCompleter() = default;

} /* namespace astviewer */
