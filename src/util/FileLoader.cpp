/*
 * FileLoader.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#include <util/FileLoader.h>

#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

#include <QDebug>

namespace astviewer {

FileLoader::FileLoader(QObject* parent) :
    QObject(parent), watcher(this), file(""), file_content("") {
  connect(&watcher, SIGNAL(finished()), this, SLOT(fileRead()));
}

void FileLoader::clear() {
  file = "";
  file_content = "";
}

void FileLoader::read(QString file) {
  this->file = file;
  QFuture<QString> result = QtConcurrent::run(astviewer::readTxtFile, file);
  //auto watcher = new QFutureWatcher<QString>(this);
  watcher.setFuture(result);
  qDebug() << "File load requested. Future started: " << result.isStarted();
}

void FileLoader::fileRead() {
  auto result = watcher.future();
  file_content = result.result();
  emit fileLoaded(file, file_content);
}

FileLoader::~FileLoader() = default;

} /* namespace astviewer */
