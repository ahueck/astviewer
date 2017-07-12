#include "gui/mainwindow.h"
#include "ui_mainwindow.h"

#include "gui/CommandInput.h"
#include "util/QLogHandler.h"
#include "core/ClangToolSession.h"

#include <QFileDialog>
#include <QPointer>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    in(nullptr)
{
    ui->setupUi(this);

    QObject::connect(astviewer::QLogHandler::instance().data(),
          SIGNAL(doLog(const QString&)),
          ui->logBrowser,
          SLOT(append(const QString&)),
          Qt::QueuedConnection
      );

    QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(openTU()));
    QObject::connect(ui->actionOpen_DB, SIGNAL(triggered()), this, SLOT(openCompilationDB()));
    //QObject::connect(ui->textInput, SIGNAL(textChanged()), this, SLOT(cmdInputChanged()));
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
  QObject::connect(session, SIGNAL(matchedAST(const QString&)), ui->textBrowserAST, SLOT(setPlainText(const QString&)));
}

void MainWindow::setSourceView(const QString& content) {
  emit ui->textBrowserSrc->insertPlainText(content);
}

void MainWindow::openTU() {
  const auto file = QFileDialog::getOpenFileName(this,
                    tr("Open Translation Unit"),
                    QString(),
                    tr("TUs (*.cpp *.c *.cc *.cxx)"));
  qDebug() << "Selected TU file " << file;
  emit selectedTU(file);
}

void MainWindow::openCompilationDB() {
  const auto file = QFileDialog::getOpenFileName(this,
                    tr("Open Compilation Database"),
                    QString(),
                    tr("TUs (*.json)"));
  qDebug() << "Selected DB file " << file;
  emit selectedCompilationDB(file);
}

MainWindow::~MainWindow() {
    delete ui;
}
