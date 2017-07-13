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

public slots:
	void openTU();
	void openCompilationDB();
	void loadFile(const QString&);
	void loadFileFinished(QString, QString);

signals:
  void selectedTU(const QString&);
  void selectedCompilationDB(const QString&);

private:
	Ui::MainWindow *ui;
	QLabel* label_status;
	astviewer::CommandInput* in;
	astviewer::FileLoader* loader;
};

#endif // MAINWINDOW_H
