/*
 * DynamicCompleter.h
 *
 *  Created on: Jul 28, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_DYNAMICCOMPLETER_H_
#define INCLUDE_CORE_DYNAMICCOMPLETER_H_

#include <QCompleter>
#include <QObject>

class QString;

namespace astviewer {

class DynamicStringListModel;

class DynamicCompleter: public QCompleter {
Q_OBJECT
protected:
  DynamicStringListModel* dyn_model { nullptr };
public:
  DynamicCompleter(QObject* parent = nullptr);
  virtual void setDynModel(DynamicStringListModel*);
  virtual ~DynamicCompleter();

public slots:
  void updateCompletion(const QString&);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_DYNAMICCOMPLETER_H_ */
