/*
 * RecentFileManager.h
 *
 *  Created on: Jul 14, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_GUI_RECENTFILEMANAGER_H_
#define INCLUDE_GUI_RECENTFILEMANAGER_H_

#include <QList>
#include <QObject>
#include <QStringList>

class QAction;
class QMenu;
class QString;

namespace astviewer {

class RecentFileManager: public QObject {
Q_OBJECT
private:
  QMenu* menu_target { nullptr };
  QList<QAction*> recentFileActions;
  QStringList files;
  static constexpr int num_recent_files = 6;
  static constexpr const char* recent_files_id = "recent_files";

public:
  explicit RecentFileManager(QObject* parent = nullptr);
  void setTopLevelMenu(QMenu* top_menu);
  ~RecentFileManager() override;

public slots:
  void updateRecentFiles(QString);
  void clearRecentFiles();

private slots:
  void openRecentFile();

signals:
  void recentFileSelected(QString);

private:
  void createAction(QAction* anchor, QString file_string);
  void handleHistory();
};

} /* namespace astviewer */

#endif /* INCLUDE_GUI_RECENTFILEMANAGER_H_ */
