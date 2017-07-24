/*
 * FileLoader.h
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_FILELOADER_H_
#define INCLUDE_UTIL_FILELOADER_H_

#include <core/Task.h>
#include <util/Util.h>

#include <QFutureWatcher>
#include <QObject>
#include <QString>

namespace astviewer {

class FileLoader: public Task {
Q_OBJECT
private:
  QFutureWatcher<Command> watcher;

public:
  explicit FileLoader(QObject* parent = nullptr);

  void fileLoad(Command) override;

  ~FileLoader() override;

private slots:
  void fileRead();
};

} /* namespace astviewer */

#endif /* INCLUDE_UTIL_FILELOADER_H_ */
