#include "networkclient.h"
<<<<<<< Updated upstream

NetworkClient*NetworkClient::instance=nullptr;


NetworkClient* NetworkClient::getInstance()
{
    if (instance == nullptr)
    {
        instance = new NetworkClient();
    }
    return instance;
}
=======
#include <qdebug.h>
NetworkClient* NetworkClient::instance = nullptr;
>>>>>>> Stashed changes

NetworkClient::NetworkClient()
{
    this->socket=new QTcpSocket();
}

<<<<<<< Updated upstream
void NetworkClient::connect(const QString &host, quint16 port)
{
    socket->connectToHost(host,port);

}


void NetworkClient::sendToServer(const QString &message)
=======
NetworkClient* NetworkClient::getInstance()
{
    if (instance == nullptr)
    {
        instance = new NetworkClient();
    }
    return instance;
}

void NetworkClient::connect(const QString &host, quint16 port)
{
    if (socket->state() != QAbstractSocket::ConnectedState)
       {
           socket->connectToHost(host, port);
           if (!socket->waitForConnected(5000))
           {
               qDebug() << "Error: " << socket->errorString();
           }
       }
    //socket->open(QIODevice::ReadWrite);
}


void NetworkClient::sendToServer(const QString message)
>>>>>>> Stashed changes
{
    if(!message.isEmpty())
    {
        socket->write(QString(message).toUtf8());
        socket->waitForBytesWritten();
    }
}

QString NetworkClient::receiveFromServer()
{
    socket->waitForReadyRead();


    QByteArray responseData = socket->readAll();
    QString response = QString::fromUtf8(responseData.constData(), responseData.length());

    return response;
}
