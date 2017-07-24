/*
 * ToolWrapper.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#include <core/ToolWrapper.h>

#include <QObject>

namespace astviewer {

ToolWrapper::ToolWrapper(QObject* parent) :
    FutureTask(parent) {

}

ToolWrapper::~ToolWrapper() = default;

} /* namespace astviewer */
