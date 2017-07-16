/*
 * FileLoader.h
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_FILELOADER_H_
#define INCLUDE_UTIL_FILELOADER_H_

#include <util/Util.h>

#include <QFutureWatcher>
#include <QObject>
#include <QString>

namespace astviewer {

class FileLoader: public QObject {
Q_OBJECT
private:
  QFutureWatcher<QString> watcher;
  QString file;
  QString file_content;

public:

  FileLoader(QObject* parent = nullptr);

  void clear();

  void read(QString file);

  ~FileLoader() override;

signals:
  void fileLoading();
  void fileLoaded(QString, QString);

private slots:
  void fileRead();
};

} /* namespace astviewer */

#endif /* INCLUDE_UTIL_FILELOADER_H_ */
