/*
 * RecentFileManager.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ahueck
 */

#include <gui/RecentFileManager.h>

#include <QAction>
#include <QFileInfo>
#include <QMenu>
#include <QSettings>
#include <QVariant>
#include <QString>

#include <stddef.h>

namespace astviewer {

RecentFileManager::RecentFileManager(QObject* parent) :
    QObject(parent) {
  QSettings settings("sc", "astviewer");
  files = settings.value(recent_files_id).toStringList();
  handleHistory();
}

void RecentFileManager::setTopLevelMenu(QMenu* top_menu) {
  menu_target = top_menu;
  if (files.empty()) {
    menu_target->setEnabled(false);
    menu_target->update();
    return;
  }
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
  files.removeAll(file);
  files.prepend(file);
  handleHistory();

  if (files.size() > recentFileActions.size()) {
    auto first = menu_target->actions().at(0);
    createAction(first, "ph");
  }

  const auto strippedName = [] (QString name) {
    return QFileInfo(name).fileName();
  };
  size_t counter = 0;
  for (auto& f : files) {
    auto action = recentFileActions[counter];
    action->setText(strippedName(f));
    action->setData(f);
    ++counter;
  }
  menu_target->setEnabled(true);
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
  this->files.clear();
  for (auto action : recentFileActions) {
    delete action;
  }
  recentFileActions.clear();
  menu_target->update();
  menu_target->setEnabled(false);
}

RecentFileManager::~RecentFileManager() {
  QSettings settings("sc", "astviewer");
  settings.setValue(recent_files_id, files);
}

} /* namespace astviewer */
