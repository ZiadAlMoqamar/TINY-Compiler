#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"
#include "gvc.h"
#include "cdt.h"
#include "cgraph.h"


void writeFile(string input,string filename) {
    ofstream out;
    out.open(filename, ios_base::app | ios_base::out);
    out << input << "\n";
    out.close();
}


void createFile(string path){
    ofstream output(path);
}

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
    ui->textEdit->clear();
    ui->textEdit->setPlainText(QString(""));
    ui->textBrowser->clear();
    ui->actionSave_Token_File->setEnabled(false);
    //ui->graphicsView->items().clear();
    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->horizontalSlider->setEnabled(false);
}


void MainWindow::on_actionScan_triggered()
{
    string scannerOutput="";
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    scannerOutput=Scanner(inFile.fileContent);
    inFile.isScanned=true;
    QString QScannerOutput = QString::fromStdString(scannerOutput);
    ui->textBrowser->setPlainText(QScannerOutput);
    ui->actionSave_Token_File->setEnabled(inFile.isScanned);
    //claering graphicsView
    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->horizontalSlider->setEnabled(false);
}


void MainWindow::on_textEdit_textChanged()
{
    if(ui->textEdit->toPlainText()==""){
        ui->actionScan->setEnabled(false);
        ui->actionParse->setEnabled(false);
    }
    else{
        if(!ui->radioButton2->isChecked()){
        ui->actionScan->setEnabled(true);
        }
        ui->actionParse->setEnabled(true);
    }
}


void MainWindow::on_actionParse_triggered()
{
    string scannerOutput="";
    vector<Token> intermediate;
    if(ui->radioButton1->isChecked()){
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    scannerOutput=Scanner(inFile.fileContent);
    inFile.isScanned=true;
    QString QScannerOutput = QString::fromStdString(scannerOutput);
    ui->textBrowser->setPlainText(QScannerOutput);
    ui->actionSave_Token_File->setEnabled(inFile.isScanned);
    intermediate=parseFileText(scannerOutput);
    }
    if(ui->radioButton2->isChecked()){
        string tokenTablestr = (ui->textEdit->toPlainText()).toStdString();
        inFile.isScanned=true;
        QString QScannerOutput = QString::fromStdString(scannerOutput);
        ui->textBrowser->setPlainText(QScannerOutput);
       // ui->actionSave_Token_File->setEnabled(inFile.isScanned);
        intermediate=parseFileText(tokenTablestr);
    }
    string  dotLangst ="";
    try {
         dotLangst=dotLang(intermediate) ;
         remove("DotGraph.txt");
        // if(errorHandler()=="NOERROR")
         writeFile(dotLangst,"DotGraph.txt");


         QProcess process;
         process.start("Graphviz\\bin\\dot",QStringList()<<"-Tsvg"<< "DotGraph.txt"<< "-o"<<"graph.svg");
         process.waitForFinished();
             //system("Graphviz\\bin\\dot -Tsvg DotGraph.txt -o graph.svg");
              //system("graph.svg");

             if(ui->checkBox->isChecked()){
                 process.start("Graphviz\\bin\\dot",QStringList()<<"-Tpng"<< "DotGraph.txt"<< "-o"<<"graph.png");
                 process.waitForFinished();
                 process.start("graph.png");
                 process.waitForFinished();
                 //system("Graphviz\\bin\\dot -Tpng DotGraph.txt -o graph.png");
                  system("graph.png");
             }
             QImage img("graph.svg");
                     bool valid = img.load(QString::fromStdString("graph.svg"));
                     if (valid) {
                         QGraphicsScene* scene = new QGraphicsScene();
                         ui->graphicsView->setScene(scene);
                         QGraphicsSvgItem * item = new QGraphicsSvgItem("graph.svg");
                         scene->addItem(item);
                         //slider = true;
                         //ui->tabWidget->setCurrentIndex(2);
                         ui->horizontalSlider->setEnabled(true);
                     }

    }  catch (const char * err) {
       QMessageBox::information(this,"Error Found",err);
    }


}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{

            QImage img("graph.svg");
            bool valid = img.load(QString::fromStdString("graph.svg"));
            if (valid) {
                QGraphicsScene* scene = new QGraphicsScene();
                ui->graphicsView->setScene(scene);
                QGraphicsSvgItem * item = new QGraphicsSvgItem("graph.svg");
            const double exp = value * 0.01;
             const double scl = pow(10.0, exp);
               item->setTransform(QTransform().scale(scl, scl));
               scene->addItem(item);
                 }
              //  qreal scaleFactor =  scl /240;

             //   qreal factor = ui->graphicsView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

            //  if (0.05 < factor && factor < 10)

                 //   ui->graphicsView->scale(scaleFactor, scaleFactor);


}


void MainWindow::on_radioButton2_clicked()
{
    if(ui->radioButton2->isChecked()){
    ui->actionScan->setEnabled(false);
    }
    else{
        ui->actionScan->setEnabled(true);
    }
}


void MainWindow::on_radioButton1_clicked()
{
    on_textEdit_textChanged();
}

