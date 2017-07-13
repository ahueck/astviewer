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
}

class QLabel;

class MainWindow: public QMainWindow {
Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	void registerInput(astviewer::CommandInput*);
	void registerClangTool(astviewer::ClangToolSession*);
	~MainWindow();

private:
	void updateRecentFileActions(QString file);

public slots:
	void openTU();
	void openCompilationDB();
	void loadFile(const QString&);
	void loadFileFinished(QString, QString);

private slots:
  void openRecentFile();

signals:
  void selectedTU(const QString&);
  void selectedCompilationDB(const QString&);

private:
  static constexpr size_t num_recent_files = 6;
  static constexpr const char* recent_files_id = "recent_files";
	Ui::MainWindow *ui;
	QLabel* label_status;
	astviewer::CommandInput* in;
	astviewer::FileLoader* loader;
	QList<QAction*> recentFileActions;
};

#endif // MAINWINDOW_H
