/*
 * RecentFileManager.h
 *
 *  Created on: Jul 14, 2017
 *      Author: ahueck
 */

#ifndef SRC_GUI_RECENTFILEMANAGER_H_
#define SRC_GUI_RECENTFILEMANAGER_H_

#include <QList>
#include <QObject>

class QMenu;
class QAction;

namespace astviewer {

class RecentFileManager : public QObject {
Q_OBJECT
private:
  QMenu* menu_target{nullptr};
  QList<QAction*> recentFileActions;
  QStringList files;
  static constexpr int num_recent_files = 6;
  static constexpr const char* recent_files_id = "recent_files";

public:
  RecentFileManager(QObject* parent = nullptr);
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

#endif /* SRC_GUI_RECENTFILEMANAGER_H_ */
