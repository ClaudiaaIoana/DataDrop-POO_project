#include "networkclient.h"
#include <qdebug.h>

NetworkClient* NetworkClient::instance = nullptr;


NetworkClient::NetworkClient()
{
    this->socket=new QTcpSocket();
}


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
           if (socket->waitForConnected(5000))
                   {
                       qDebug() << "Connected to" << host << "on port" << port;
                   }
                   else
                   {
                       qDebug() << "Error: " << socket->errorString();
                   }
       }
}


void NetworkClient::sendToServer(const QString message)
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
