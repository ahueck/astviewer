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
#include <qstatusbar.h>
#include <qaction.h>
#include <qvariant.h>

#include <waitingspinnerwidget.h>

namespace astviewer {

inline QString readTxtFile(QString file_path) {
  QFile file(file_path);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return {""};
  }
  QTextStream in(&file);
  return in.readAll();
}

class ProcessHandler : public QObject {
  Q_OBJECT

private:
  WaitingSpinnerWidget spinner;
  QWidgetList widgets;
  QList<QAction* > actions;
  QStatusBar* status;

public:
  ProcessHandler(QObject* parent = 0) : QObject(parent), spinner(0, false, false), status(nullptr) {
    spinner.setLineLength(5);
    spinner.setInnerRadius(5);
  }

  void setStatus(QStatusBar* status) {
    this->status = status;
    status->insertPermanentWidget(0, &spinner, 0);
  }

  void addWidget(QWidget* widget) {
    widgets.push_back(widget);
  }

  void addWidgets(std::initializer_list<QWidget*> widgets) {
    for(auto widget : widgets) {
      this->widgets.push_back(widget);
    }
  }

  void addAction(QAction* widget) {
    actions.push_back(widget);
  }

  void addActions(std::initializer_list<QAction*> actions) {
    for(auto action: actions) {
      this->actions.push_back(action);
    }
  }

  void clear() {
    widgets.clear();
    actions.clear();
  }
  virtual ~ProcessHandler() {

  }

public slots:
  void processStarted(QString msg) {
    for(auto widget : widgets) {
      widget->setEnabled(false);
    }
    for(auto action: actions) {
      action->setEnabled(false);
    }
    if(status) {
      spinner.start();
      status->showMessage(msg);
    }
  }

  void processFinished() {
    if(status) {
      status->clearMessage();
      spinner.stop();
    }
    for(auto widget : widgets) {
      widget->setEnabled(true);
    }
    for(auto action: actions) {
      action->setEnabled(true);
    }
  }
};

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
  void fileLoading();
  void fileLoaded(QString, QString);
};

}

#endif /* INCLUDE_UTIL_UTIL_H_ */
