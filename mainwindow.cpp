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


void MainWindow::on_actionSave_Token_File_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    //.xml or .json according to output global var type
    QString fileExtension = "txt";
    QFile file(fileName+"."+fileExtension);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    QString text = ui->textBrowser->toPlainText();
    out << text;
    file.close();

}


void MainWindow::on_actionNew_triggered()
{
    inputFieldFile.clear();
    ui->textEdit->setPlainText(QString());
    ui->textBrowser->clear();
    ui->actionSave_Token_File->setEnabled(false);
}


void MainWindow::on_actionScan_triggered()
{
    string scannerOutput;
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    scannerOutput=Scanner(inFile.fileContent);
    inFile.isScanned=true;
    QString QScannerOutput = QString::fromStdString(scannerOutput);
    ui->textBrowser->setPlainText(QScannerOutput);
    ui->actionSave_Token_File->setEnabled(inFile.isScanned);
}


void MainWindow::on_textEdit_textChanged()
{
    if(ui->textEdit->toPlainText()==""){
        ui->actionScan->setEnabled(false);
    }
    else{
        ui->actionScan->setEnabled(true);
    }
}

