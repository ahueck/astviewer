/*
 * DynamicCompleter.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: ahueck
 */

#include <core/DynamicCompleter.h>
#include <core/DynamicStringListModel.h>

#include <QString>
#include <QtDebug>

namespace astviewer {

DynamicCompleter::DynamicCompleter(QObject* parent) : QCompleter(parent) {

}

void DynamicCompleter::setDynModel(DynamicStringListModel* m) {
  this->dyn_model = m;
  this->setModel(m);
}

void DynamicCompleter::updateCompletion(const QString& line, const QString& prefix, int cursor_pos) {
  qDebug() << "Update internal model with prefix: " << prefix;
  dyn_model->updateModelList(line, prefix, cursor_pos);
  QCompleter::setCompletionPrefix(prefix);
}

DynamicCompleter::~DynamicCompleter() = default;

} /* namespace astviewer */
