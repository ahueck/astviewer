/*
 * FileLoader.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: ahueck
 */

#include <util/FileLoader.h>
#include <util/Util.h>

#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

#include <QDebug>

namespace astviewer {

FileLoader::FileLoader(QObject* parent) :
    FutureTask(parent) {
}

void FileLoader::fileLoad(Command cmd) {
  auto load_func = [](Command cmd) -> Command {
    auto file = cmd.input;
    cmd.result = readTxtFile(file);
    return cmd;
  };
  qDebug() << "File load requested.";
  run(load_func, cmd);
}

FileLoader::~FileLoader() = default;

} /* namespace astviewer */
