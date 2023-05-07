#include "mainwindow.h"
#include "appinterface.h"
#include <QApplication>
#include "networkclient.h"
#include "user.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    NetworkClient* networkManager=NetworkClient::getInstance();
    networkManager->connect("172.20.10.2",5555);
    w.show();

    return a.exec();
}
