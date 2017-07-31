/*
 * DynamicStringListModel.h
 *
 *  Created on: Jul 28, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_DYNAMICSTRINGLISTMODEL_H_
#define INCLUDE_CORE_DYNAMICSTRINGLISTMODEL_H_

#include <QStringListModel>
#include <QObject>

class QString;

namespace astviewer {

class DynamicStringListModel: public QStringListModel {
Q_OBJECT
public:
  DynamicStringListModel(QObject* parent = nullptr);
  virtual ~DynamicStringListModel();

public slots:
  virtual void updateModelList(const QString& line, const QString& prefix, int cursor_pos = 0);

signals:
  void modelUpdated(bool);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_DYNAMICSTRINGLISTMODEL_H_ */
