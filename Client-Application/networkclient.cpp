#include "networkclient.h"

NetworkClient*NetworkClient::instance=nullptr;


NetworkClient* NetworkClient::getInstance()
{
    if (instance == nullptr)
    {
        instance = new NetworkClient();
    }
    return instance;
}

NetworkClient::NetworkClient()
{

    this->socket=new QTcpSocket();

}

void NetworkClient::connect(const QString &host, quint16 port)
{
    socket->connectToHost(host,port);

}


void NetworkClient::sendToServer(const QString &message)
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
