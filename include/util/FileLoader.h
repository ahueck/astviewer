/*
 * FileLoader.h
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_FILELOADER_H_
#define INCLUDE_UTIL_FILELOADER_H_

#include <core/FutureTask.h>
#include <core/Command.h>

#include <QObject>
#include <QString>

namespace astviewer {

class FileLoader: public FutureTask {
Q_OBJECT
public:
  explicit FileLoader(QObject* parent = nullptr);

  void fileLoad(Command) override;

  ~FileLoader() override;
};

} /* namespace astviewer */

#endif /* INCLUDE_UTIL_FILELOADER_H_ */
