#include "gui/mainwindow.h"
#include "ui_mainwindow.h"

#include "gui/CommandInput.h"
#include "util/QLogHandler.h"
#include "util/Util.h"
#include "core/ClangToolSession.h"

#include <QFileDialog>
#include <QPointer>
#include <QDebug>
#include <QLabel>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    label_status(nullptr),
    in(nullptr),
    loader(new astviewer::FileLoader(this))
{
    ui->setupUi(this);

    /*
    label_status = new QLabel(this);
    label_status->setText("Status");
    ui->statusBar->addPermanentWidget(label_status);
    ui->statusBar->showMessage("Testing a message here");
    */

    QObject::connect(astviewer::QLogHandler::instance().data(),
          SIGNAL(doLog(const QString&)),
          ui->logBrowser,
          SLOT(appendPlainText(const QString&)),
          Qt::QueuedConnection
      );


    QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(openTU()));
    QObject::connect(ui->actionOpen_DB, SIGNAL(triggered()), this, SLOT(openCompilationDB()));

    QObject::connect(loader, SIGNAL(fileLoaded(QString, QString)), this, SLOT(loadFileFinished(QString, QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(selectedTU(const QString&)), this, SLOT(loadFile(const QString&)));
}

void MainWindow::registerInput(astviewer::CommandInput* in) {
  this->in = in;
  in->setParent(ui->tabInput);

  in->setObjectName(QStringLiteral("textInput"));

  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(in->sizePolicy().hasHeightForWidth());
  in->setSizePolicy(sizePolicy);

  in->setMaximumSize(QSize(16777215, 400));

  ui->gridLayout->addWidget(in, 0, 0, 1, 1);
}

void MainWindow::registerClangTool(astviewer::ClangToolSession* session) {
  QObject::connect(this, SIGNAL(selectedTU(const QString&)), session, SLOT(loadTU(const QString&)));
  QObject::connect(this, SIGNAL(selectedCompilationDB(const QString&)), session, SLOT(loadCompilationDB(const QString&)));

  QObject::connect(in, SIGNAL(commandEntered(const QString&)), session, SLOT(commandInput(const QString&)));
  QObject::connect(session, SIGNAL(matchedAST(const QString&)), ui->plainTextEditAST, SLOT(setPlainText(const QString&)));
}

void MainWindow::loadFileFinished(QString file, QString content) {
  emit ui->plainTextEditSrc->insertPlainText(content);
  ui->actionOpen_File->setEnabled(true);
  ui->actionOpen_DB->setEnabled(true);
  in->setEnabled(true);
}

void MainWindow::loadFile(const QString& file) {
  ui->actionOpen_File->setEnabled(false);
  ui->actionOpen_DB->setEnabled(false);
  in->setEnabled(false);
  loader->read(file);
}

void MainWindow::openTU() {
  const auto file = QFileDialog::getOpenFileName(this,
                    tr("Open Translation Unit"),
                    QString(),
                    tr("Translation Unit (*.cpp *.c *.cc *.cxx)"));
  qDebug() << "Selected TU file " << file;
  emit selectedTU(file);
}

void MainWindow::openCompilationDB() {
  const auto file = QFileDialog::getOpenFileName(this,
                    tr("Open Compilation Database"),
                    QString(),
                    tr("Compilation Database (*.json)"));
  qDebug() << "Selected DB file " << file;
  emit selectedCompilationDB(file);
}

MainWindow::~MainWindow() {
    delete ui;
}
