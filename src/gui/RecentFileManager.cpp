/*
 * RecentFileManager.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ahueck
 */

#include "gui/RecentFileManager.h"

#include <qmenu.h>
#include <qaction.h>
#include <qsettings.h>
#include <QFileInfo>
#include <QDebug>

namespace astviewer {

RecentFileManager::RecentFileManager(QObject* parent) :
    QObject(parent), menu_target(nullptr) {
  QSettings settings("sc", "astviewer");
  files = settings.value(recent_files_id).toStringList();
  handleHistory();
}

void RecentFileManager::setTopLevelMenu(QMenu* top_menu) {
  menu_target = top_menu;
  auto first = menu_target->actions().at(0);
  for (auto& file_string : files) {
    createAction(first, file_string);
  }
  menu_target->update();
}

void RecentFileManager::openRecentFile() {
  auto action = qobject_cast<QAction *>(sender());
  if (action) {
    emit recentFileSelected(action->data().toString());
  }
}

void RecentFileManager::updateRecentFiles(QString file) {
  qDebug() << file;
  auto rm_result = files.removeAll(file);
  files.prepend(file);
  handleHistory();

  const auto diff = files.size() - this->recentFileActions.size();
  if (diff > 0) {
    auto first = menu_target->actions().at(0);
    createAction(first, "ph");
  }

  int counter = 0;
  const auto strippedName = [] (QString name) {
    return QFileInfo(name).fileName();
  };
  for (auto& f : files) {
    qDebug() << "Update: " << strippedName(f);
    auto action = recentFileActions[counter];
    action->setText(strippedName(f));
    action->setData(f);
    ++counter;
  }
  menu_target->update();
}

void RecentFileManager::createAction(QAction* anchor, QString file_string) {
  const auto strippedName = [] (QString name) {
    return QFileInfo(name).fileName();
  };
  auto* action = new QAction(this);
  action->setText(strippedName(file_string));
  action->setData(file_string);
  connect(action, SIGNAL(triggered()), this, SLOT(openRecentFile()));
  this->recentFileActions.push_back(action);
  menu_target->insertAction(anchor, action);
}

void RecentFileManager::handleHistory() {
  if (files.size() > num_recent_files) {
    files.removeLast();
  }
}

void RecentFileManager::clearRecentFiles() {

}

RecentFileManager::~RecentFileManager() {
  QSettings settings("sc", "astviewer");
  settings.setValue(recent_files_id, files);
}

} /* namespace astviewer */
