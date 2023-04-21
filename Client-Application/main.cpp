#include "mainwindow.h"
#include "appinterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setStyleSheet("background-image:url(:backgroundmainwindow.jpg)");
    w.show();

    return a.exec();
}
