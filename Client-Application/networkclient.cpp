#include "networkclient.h"


NetworkClient::NetworkClient()
{

    this->socket=new QTcpSocket();

}

void NetworkClient::connect()
{
    socket->connectToHost("172.16.33.91",quint16(5555));
    socket->open(QIODevice::ReadWrite);
}


void NetworkClient::sendToServer(QString message)
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
