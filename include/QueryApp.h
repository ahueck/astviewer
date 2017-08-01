/*
 * QueryApp.h
 *
 *  Created on: Jul 20, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_QUERYAPP_H_
#define INCLUDE_QUERYAPP_H_

#include "core/CoreManager.h"

namespace av = astviewer;

namespace astviewer {
class QueryCompleterList;
class DynamicCompleter;
}

class QueryApp: public av::CoreManager {
Q_OBJECT
private:
  av::QueryCompleterList* m { nullptr };
  av::DynamicCompleter* c { nullptr };

public:
  QueryApp();
  void createInputWidget() override;
  void createClangSession() override;
  virtual ~QueryApp();
};

#endif /* INCLUDE_QUERYAPP_H_ */
