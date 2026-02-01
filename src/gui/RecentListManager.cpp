/*
 * RecentListManager.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ahueck
 */

#include <gui/RecentListManager.h>
#include <util/Util.h>

#include <QAction>
#include <QFileInfo>
#include <QMenu>
#include <QSettings>
#include <QString>
#include <QVariant>

#include <stddef.h>

namespace astviewer {

RecentListManager::RecentListManager(QString settings_id, int max_items, int path_components,
                                   QObject* parent)
    : QObject(parent),
      max_items(max_items),
      path_components(path_components),
      settings_id(settings_id) {
  QSettings settings("sc", "astviewer");
  items = settings.value(settings_id).toStringList();
  handleHistory();
}

void RecentListManager::setTopLevelMenu(QMenu* top_menu) {
  menu_target = top_menu;
  if (items.empty()) {
    menu_target->setEnabled(false);
    menu_target->update();
    return;
  }
  auto first = menu_target->actions().at(0);
  for (auto& item_string : items) {
    createAction(first, item_string);
  }
  menu_target->update();
}

void RecentListManager::openRecentItem() {
  auto action = qobject_cast<QAction*>(sender());
  if (action) {
    emit itemSelected(action->data().toString());
  }
}

void RecentListManager::updateRecentItems(QString item) {
  items.removeAll(item);
  items.prepend(item);
  handleHistory();

  if (items.size() > recentActions.size()) {
    auto first = menu_target->actions().at(0);
    createAction(first, "ph");
  }

  size_t counter = 0;
  for (auto& f : items) {
    auto action = recentActions[counter];
    action->setText(shortenPath(f, path_components));
    action->setToolTip(f);
    action->setData(f);
    ++counter;
  }
  menu_target->setEnabled(true);
  menu_target->update();
}

void RecentListManager::createAction(QAction* anchor, QString item_string) {
  auto* action = new QAction(this);
  action->setText(shortenPath(item_string, path_components));
  action->setToolTip(item_string);
  action->setData(item_string);
  connect(action, SIGNAL(triggered()), this, SLOT(openRecentItem()));
  this->recentActions.push_back(action);
  menu_target->insertAction(anchor, action);
}

void RecentListManager::handleHistory() {
  while (items.size() > max_items) {
    items.removeLast();
  }
}

void RecentListManager::clearRecentItems() {
  this->items.clear();
  for (auto action : recentActions) {
    delete action;
  }
  recentActions.clear();
  menu_target->update();
  menu_target->setEnabled(false);
}

RecentListManager::~RecentListManager() {
  QSettings settings("sc", "astviewer");
  settings.setValue(settings_id, items);
}

} /* namespace astviewer */