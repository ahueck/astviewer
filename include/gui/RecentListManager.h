/*
 * RecentListManager.h
 *
 *  Created on: Jul 14, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_RECENTLISTMANAGER_H_
#define INCLUDE_GUI_RECENTLISTMANAGER_H_

#include <QList>
#include <QObject>
#include <QStringList>

class QAction;
class QMenu;
class QString;

namespace astviewer {

class RecentListManager : public QObject {
  Q_OBJECT
 private:
  QMenu* menu_target{nullptr};
  QList<QAction*> recentActions;
  QStringList items;
  int max_items;
  QString settings_id;

 public:
  explicit RecentListManager(QString settings_id, int max_items = 6, QObject* parent = nullptr);
  void setTopLevelMenu(QMenu* top_menu);
  ~RecentListManager() override;

 public slots:
  void updateRecentItems(QString);
  void clearRecentItems();

 private slots:
  void openRecentItem();

 signals:
  void itemSelected(QString);

 private:
  void createAction(QAction* anchor, QString item_string);
  void handleHistory();
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_RECENTLISTMANAGER_H_ */