#include "networkclient.h"
#include <qdebug.h>
#include <QFile>
#include <QFileInfo>
#include "serverlistener.h"

NetworkClient* NetworkClient::instance = nullptr;


NetworkClient::NetworkClient()
{
    this->socket=new QTcpSocket();
    this->mutex=new QMutex();
}

 QTcpSocket *NetworkClient::getSocket()
 {
    return socket;
 }

NetworkClient* NetworkClient::getInstance()
{
    if (instance == nullptr)
    {
        instance = new NetworkClient();
    }
    return instance;
}

QMutex* NetworkClient::getMutex()
{
    return this->mutex;
}

void NetworkClient::connect(const QString &host, quint16 port)
{
    mutex->lock();
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
    mutex->unlock();
}

void NetworkClient::sendFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file " << filePath;
        return;
    }

    QFileInfo fileInfo(file);
    QString fileName(fileInfo.fileName());
    QByteArray fileData = file.readAll();
    qint64 fileSize = file.size();

    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << fileName << fileSize << fileData;

    if (socket->write(byteArray) == -1) {
        qDebug() << "Error writing to socket: " << socket->errorString();
    }
}

void NetworkClient::sendToServer(const QString message)
{
    mutex->lock();
    if(!message.isEmpty())
    {
        socket->write(QString(message).toUtf8());
        socket->waitForBytesWritten();
    }
    mutex->unlock();
}

QString NetworkClient::receiveFromServer()
{
    mutex->lock();
    socket->waitForReadyRead();
    QByteArray responseData = socket->readAll();
    QString response = QString::fromUtf8(responseData.constData(), responseData.length());
    mutex->unlock();
    return response;
}
