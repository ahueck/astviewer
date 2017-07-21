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
}

class QLabel;
class QStatusBar;
class QWidget;

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

public slots:
  void setSource(QString);
  void setClangAST(QString);
  void fileLoadFinished(QString);

protected slots:
  void openTU();
  void openCompilationDB();
  void recentFileLoad(QString);

private:
  Ui::MainWindow *ui;
  astviewer::CommandInput* in { nullptr };
  astviewer::RecentFileManager* recent_files { nullptr };
};

#endif // MAINWINDOW_H

