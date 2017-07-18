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
	StatusHandler pm;
	CommandInput* input{nullptr};
	MainWindow* win{nullptr};
	ClangToolSession* session{nullptr};
	// QMap<QString, QVariantList> lockGroups; -> lockGroups to iterate over and setEnabled(true|false); for now handled by signal and slots
	// Connect TaskManager with ProcessHandler to generically show status messages (commandExecute and taskDone)
	// Connect a Task with this (to handle unlocking of GUI elements and pass data appropriately) and add to TaskManager

public:
	CoreManager(MainWindow* win);
	virtual ~CoreManager();

public slots:
  void selectedTU(QString);
  void handleFinished(Command);

signals:
  void loadFile(Command);
  void lockFileLoad(bool);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_COREMANAGER_H_ */
