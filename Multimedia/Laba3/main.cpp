#include "mainwindow.h"
#include "histogram.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    w.QMainWindow::show();
    return a.exec();
}
