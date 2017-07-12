#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace astviewer {
  class ClangToolSession;
  class CommandInput;
}

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
	void setSourceView(const QString&);

signals:
  void selectedTU(const QString&);
  void selectedCompilationDB(const QString&);

private:
	Ui::MainWindow *ui;
	astviewer::CommandInput* in;
};

#endif // MAINWINDOW_H
