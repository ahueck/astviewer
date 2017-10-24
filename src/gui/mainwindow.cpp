#include <gui/mainwindow.h>
#include <ui_mainwindow.h>

#include <core/CoreManager.h>

#include <gui/CommandInput.h>
#include <gui/RecentFileManager.h>
#include <gui/CompilationDbDelegate.h>
#include <gui/LineTextEdit.h>
#include <gui/SelectionProvider.h>

#include <util/FileLoader.h>
#include <util/QLogHandler.h>
#include <util/Util.h>

#include <QFileDialog>
#include <QPointer>
#include <QDebug>
#include <QLabel>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), recent_files(
        new astviewer::RecentFileManager(this)) {
  ui->setupUi(this);

  dbViewModel = new QStringListModel(this);
  this->ui->listViewCompDB->setModel(dbViewModel);
  auto delegate = new astviewer::CompilationDbDelegate(
      this->ui->listViewCompDB);
  this->ui->listViewCompDB->setItemDelegate(delegate);

  src_edit = new astviewer::LineTextEdit(ui->widgetSrc);
  src_edit->setObjectName(QStringLiteral("plainTextEditSrc"));
  ui->verticalLayout->addWidget(src_edit);

  this->selection_notifier = new astviewer::SelectionProvider(this);
  selection_notifier->installOn(src_edit);

  query_edit = new astviewer::LineTextEdit(ui->widgetQuery);
  query_edit->setObjectName(QStringLiteral("plainTextEditAST"));
  query_edit->setAcceptDrops(false);
  query_edit->setUndoRedoEnabled(false);
  query_edit->setReadOnly(true);
  query_edit->showLine(false);
  ui->verticalLayout_query->addWidget(query_edit);

  selection_edit = new astviewer::LineTextEdit(ui->widgetSelection);
  selection_edit->setObjectName(QStringLiteral("plainTextEditSelection"));
  selection_edit->setAcceptDrops(false);
  selection_edit->setUndoRedoEnabled(false);
  selection_edit->setReadOnly(true);
  selection_edit->showLine(true);
  ui->verticalLayout_selection->addWidget(selection_edit);

  // Logging:
  QObject::connect(&astviewer::QLogHandler::instance(),
      SIGNAL(doLog(const QString&)), ui->logBrowser,
      SLOT(appendPlainText(const QString&)), Qt::QueuedConnection);

  // Recent file management:
  recent_files->setTopLevelMenu(ui->menuRecent_File);
  QObject::connect(recent_files, SIGNAL(recentFileSelected(QString)), this,
      SLOT(recentFileLoad(QString)));
  QObject::connect(ui->actionClear_Menu, SIGNAL(triggered()), recent_files,
      SLOT(clearRecentFiles()));

  // Open action -> file / db:
  QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this,
      SLOT(openTU()));
  QObject::connect(ui->actionOpen_DB, SIGNAL(triggered()), this,
      SLOT(openCompilationDB()));

  QObject::connect(ui->listViewCompDB,
      SIGNAL(doubleClicked(const QModelIndex&)), this,
      SLOT(clickedDBView(const QModelIndex&)));
}

void MainWindow::registerInput(astviewer::CommandInput* in) {
  this->in = in;
//in->setParent(ui->tabInput);

  in->setObjectName(QStringLiteral("textInput"));

  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(in->sizePolicy().hasHeightForWidth());
  in->setSizePolicy(sizePolicy);

  in->setMaximumSize(QSize(16777215, 400));

  ui->gridLayout->addWidget(in, 0, 0, 1, 1);

  in->setFocus(Qt::FocusReason::OtherFocusReason);
}

void MainWindow::registerWithManager(astviewer::CoreManager* cm) {

  QObject::connect(cm, SIGNAL(fileLoadUnlock(bool)), ui->actionOpen_DB,
      SLOT(setEnabled(bool)));
  QObject::connect(cm, SIGNAL(fileLoadUnlock(bool)), ui->actionOpen_File,
      SLOT(setEnabled(bool)));

}

QStatusBar* MainWindow::getStatusbar() {
  return ui->statusBar;
}

void MainWindow::updateDbView(QStringList list) {
  dbViewModel->setStringList(list);
}

void MainWindow::clickedDBView(const QModelIndex& index) {
  QString item_text = index.data(Qt::DisplayRole).toString();
  emit selectedDbListItem(item_text);
}

void MainWindow::setSource(QString source) {
  src_edit->clear();
  src_edit->insertPlainText(source);
}

void MainWindow::setClangAST(QString source) {
  ui->tabWidgetTools->setCurrentWidget(ui->widgetSelection);
  selection_edit->clear();
  selection_edit->insertPlainText(source);
  selection_edit->ensureCursorVisible();
}

void MainWindow::setClangQuery(QString source) {
  ui->tabWidgetTools->setCurrentWidget(ui->widgetQuery);
  query_edit->clear();
  query_edit->insertPlainText(source);
  query_edit->ensureCursorVisible();
}

void MainWindow::fileLoadFinished(QString file) {
  recent_files->updateRecentFiles(file);
}

void MainWindow::recentFileLoad(QString recent_file) {
  emit selectedTU(recent_file);
}

void MainWindow::openTU() {
  const auto file = QFileDialog::getOpenFileName(this,
      tr("Open Translation Unit"), QString(),
      tr("Translation Unit (*.cpp *.c *.cc *.cxx)"));
  qDebug() << "Selected TU file " << file;

  if (file == "") {
    return;
  }

  emit selectedTU(file);
}

void MainWindow::openCompilationDB() {
  const auto file = QFileDialog::getOpenFileName(this,
      tr("Open Compilation Database"), QString(),
      tr("Compilation Database (*.json)"));
  qDebug() << "Selected DB file " << file;

  if (file == "") {
    return;
  }

  emit selectedCompilationDB(file);
}

MainWindow::~MainWindow() {
  delete ui;
}
