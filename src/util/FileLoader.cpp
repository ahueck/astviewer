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
    QObject(parent), watcher(this) {
  connect(&watcher, SIGNAL(finished()), this, SLOT(fileRead()));
}

void FileLoader::fileLoad(Command cmd) {
	auto load_func = [](Command cmd) -> Command {
		auto file = cmd.input;
		cmd.result = readTxtFile(file);
		return cmd;
	};
	qDebug() << "File load requested.";
	QFuture<Command> result = QtConcurrent::run(load_func, cmd);
	watcher.setFuture(result);
}

void FileLoader::fileRead() {
  auto result = watcher.future().result();
  emit commandFinished(result);
}

FileLoader::~FileLoader() = default;

} /* namespace astviewer */
