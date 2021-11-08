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

