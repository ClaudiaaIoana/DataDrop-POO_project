#include "mainwindow.h"
#include "appinterface.h"
#include <QApplication>
#include "networkclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // NetworkClient* networkManager=NetworkClient::getInstance();
    w.show();

    return a.exec();
}
