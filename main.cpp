#include "mainwindow.h"
#include "inputfile.h"
#include <QApplication>

InputFile inFile = InputFile();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
