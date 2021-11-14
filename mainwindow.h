#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "scanner.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_Token_File_triggered();

    void on_actionNew_triggered();

    void on_actionScan_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QString inputFieldFile = "";
    QString scannerFieldFile = "";
};
#endif // MAINWINDOW_H
