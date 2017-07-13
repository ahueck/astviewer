/*
 * uTIL.H
 *
 *  Created on: Jul 13, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_UTIL_H_
#define INCLUDE_UTIL_UTIL_H_

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>

namespace astviewer {

inline QString readTxtFile(QString file_path) {
  QFile file(file_path);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return {""};
  }
  QTextStream in(&file);
  return in.readAll();
}

class FileLoader : public QObject {
  Q_OBJECT
public:
  QFutureWatcher<QString> watcher;
  QString file;
  QString file_content;

  FileLoader(QObject* parent = 0) : QObject(parent), watcher(this), file(""), file_content("") {
    connect(&watcher, SIGNAL(finished()), this, SLOT(fileRead()));
  }

  virtual ~FileLoader() {

  }

  void clear() {
    file = {""};
    file_content = {""};
  }

  void read(QString file) {
    this->file = file;
    QFuture<QString> result = QtConcurrent::run(astviewer::readTxtFile, file);
    //auto watcher = new QFutureWatcher<QString>(this);
    watcher.setFuture(result);
    qDebug() << "File load requested. Future started: " << result.isStarted();
  }

private slots:
  void fileRead() {
    auto result = watcher.future();
    file_content = result.result();
    emit fileLoaded(file, file_content);
  }

signals:
  void fileLoaded(QString, QString);
};

}

#endif /* INCLUDE_UTIL_UTIL_H_ */
