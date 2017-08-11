#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace astviewer {
class CommandInput;
class RecentFileManager;
class CoreManager;
class LineTextEdit;
}

class QLabel;
class QStatusBar;
class QWidget;
class QListView;
class QModelIndex;
class QStringListModel;

class MainWindow: public QMainWindow {
Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  void registerInput(astviewer::CommandInput*);
  void registerWithManager(astviewer::CoreManager*);
  QStatusBar* getStatusbar();
  ~MainWindow() override;

signals:
  void selectedTU(QString);
  void selectedCompilationDB(QString);
  void selectedDbListItem(QString);

public slots:
  void setSource(QString);
  void setClangAST(QString);
  void fileLoadFinished(QString);
  void updateDbView(QStringList);

protected slots:
  void openTU();
  void openCompilationDB();
  void recentFileLoad(QString);
  void clickedDBView(const QModelIndex& index);

private:
  Ui::MainWindow *ui;
  astviewer::CommandInput* in { nullptr };
  astviewer::RecentFileManager* recent_files { nullptr };
  astviewer::LineTextEdit* src_edit { nullptr };
  astviewer::LineTextEdit* ast_edit { nullptr };
  QStringListModel* dbViewModel { nullptr };
};

#endif // MAINWINDOW_H

