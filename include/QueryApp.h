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

class QueryApp: public av::CoreManager {
Q_OBJECT
public:
  QueryApp();
  void createClangSession() override;
  virtual ~QueryApp();
};

#endif /* INCLUDE_QUERYAPP_H_ */
