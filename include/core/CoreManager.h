/*
 * CoreManager.h
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_COREMANAGER_H_
#define INCLUDE_CORE_COREMANAGER_H_

#include <QObject>

#include <core/TaskManager.h>
#include <core/Task.h>
#include <util/ProcessHandler.h>

class MainWindow;

namespace astviewer {

class CommandInput;
class ClangToolSession;

class CoreManager : public QObject {
Q_OBJECT
private:
	TaskManager tm;
	ProcessHandler pm;
	CommandInput* input{nullptr};
	MainWindow* win{nullptr};
	ClangToolSession* session{nullptr};

	// Connect TaskManager with ProcessHandler to generically show status messages (commandExecute and taskDone)
	// Connect a Task with this (to handle unlocking of GUI elements and pass data appropriately) and add to TaskManager

public:
	CoreManager();
	virtual ~CoreManager();
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_COREMANAGER_H_ */
