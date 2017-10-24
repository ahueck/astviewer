/*
 * CoreManager.h
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_COREMANAGER_H_
#define INCLUDE_CORE_COREMANAGER_H_

#include <core/Task.h>
#include <core/TaskManager.h>
#include <util/StatusHandler.h>

#include <QObject>

class MainWindow;
class QString;

namespace astviewer {

class CommandInput;
class Command;
class Task;

// QMap<QString, QVariantList> lockGroups; -> lockGroups to iterate over and setEnabled(true|false); for now handled by signal and slots
// Connect TaskManager with ProcessHandler to generically show status messages (commandExecute and taskDone)

class CoreManager: public QObject {
Q_OBJECT
protected:
  TaskManager tm;
  StatusHandler pm;

  MainWindow* win { nullptr };
  CommandInput* input { nullptr };

  Task* clang_session { nullptr };
  Task* f_loader { nullptr };

public:
  CoreManager();
  void init(MainWindow* win);
  virtual ~CoreManager();

protected:
  virtual void createFileLoader();
  virtual void createInputWidget() = 0;
  virtual void createClangSession() = 0;
  virtual void connectFileLoader();
  virtual void connectClangSession();
  virtual void postInit();

protected slots:
  // General TaskMangaer related connection:
  void handleFinished(Command);
  // SPecific Task connection (clang tooling and file IO tasks)
  void sourceLoaded(Command);
  void clangResult(Command);
  // CommandInput "console" connections:
  void commandInput(QString);
  // File IO through GUI mainwindow
  void selectedTU(QString);
  void selectedCompilationDB(QString);
  void sourceSelected(unsigned, unsigned);

signals:
  //void dispatchCommand(Command);
  void fileLoadUnlock(bool);
  void queryUnlock(bool);
  void selectionUnlock(bool);
  void compilationDbUnlock(bool);
};

} /* namespace astviewer */

#endif /* INCLUDE_CORE_COREMANAGER_H_ */

