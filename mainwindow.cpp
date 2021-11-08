#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     this->setCentralWidget(ui->groupBox);
    setWindowTitle("TINY Compiler");
    ui->textEdit->setLineWrapMode(QTextEdit::LineWrapMode(0));
    ui->textBrowser->setLineWrapMode(QTextEdit::LineWrapMode(0));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
      QFile file(fileName);
      inputFieldFile = fileName;
      if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        inFile.fileContent=text.toStdString();
        ui->textEdit->setPlainText(text);
        file.close();
}

