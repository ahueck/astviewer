/*
 * ToolWrapper.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#include <core/ToolWrapper.h>
#include <core/FutureTask.h>

namespace astviewer {

ToolWrapper::ToolWrapper(QObject* parent) :
    FutureTask(parent) {

}

ToolWrapper::~ToolWrapper() = default;

} /* namespace astviewer */
