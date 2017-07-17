#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace astviewer {
class ClangToolSession;
class CommandInput;
class FileLoader;
class RecentFileManager;
class ProcessHandler;
}

class QLabel;

class MainWindow: public QMainWindow {
Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  void registerInput(astviewer::CommandInput*);
  void registerClangTool(astviewer::ClangToolSession*);
  ~MainWindow() override;

public slots:
  void openTU();
  void openCompilationDB();
  void loadFile(const QString&);
  void loadFileFinished(QString, QString);

signals:
  void selectedTU(const QString&);
  void selectedCompilationDB(const QString&);
  void fileLoaded(QString);

private:
  Ui::MainWindow *ui;
  QLabel* label_status { nullptr };
  astviewer::CommandInput* in { nullptr };
  astviewer::FileLoader* loader;
  astviewer::RecentFileManager* file_manager;
  astviewer::ProcessHandler* p_handler;
};

#endif // MAINWINDOW_H
