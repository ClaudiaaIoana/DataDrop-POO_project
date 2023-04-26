#include "serverlistener.h"
#include "networkclient.h"
#include <QDebug>
#include "networkclient.h"
#include <QThread>

ServerListener * ServerListener::instanta=nullptr;

ServerListener::ServerListener(QObject *parent)
    : QObject{parent}
{
    NetworkClient *ManagerNetwork=NetworkClient::getInstance();
    this->socket=ManagerNetwork->getSocket();
    this->mutex=ManagerNetwork->getMutex();
}


ServerListener * ServerListener::getInstanta()
{
   if(instanta==nullptr)
   {
       instanta = new ServerListener();
   }
   return instanta;
}

void ServerListener::startListening() {
    QThread* listenerThread = new QThread();
       moveToThread(listenerThread);
       connect(listenerThread, &QThread::started, this, [this]() {
           while (true) {
               mutex->lock();
               if (socket->waitForReadyRead(-1)) {
                   QByteArray data = socket->read(2);
                   int dataSize = data.toInt();
                   QByteArray payload = socket->read(dataSize);
                   qDebug() << payload;
               }
               mutex->unlock();
           }
       });
       listenerThread->start();
}

void ServerListener::sendData(const QByteArray& data) {
    mutex->lock();
    socket->write(data);
    socket->waitForBytesWritten();
    mutex->unlock();

}
