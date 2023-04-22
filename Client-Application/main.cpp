#include "mainwindow.h"
#include "appinterface.h"
#include <QApplication>
#include "networkclient.h"
#include "user.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    NetworkClient* networkManager=NetworkClient::getInstance();
    networkManager->connect("172.16.33.91",5555);

     w.show();
   // User *user =new User("andreiungureanu133@yahoo.com","Andrei",
   //                      {"Bogdan132","Daniel_Minu123","Banica_Boss","GheScu","Mihaela","George","Emanuel","Tarcisiu","Claudia","Doraa"},
   //                      {"C112E","Moldovenii","Plutonul2"});
   // AppInterface app(user);
   // app.show();
    return a.exec();
}
