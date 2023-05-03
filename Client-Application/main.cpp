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
    networkManager->connect("172.16.33.77",5555);
    w.show();

    return a.exec();
}
