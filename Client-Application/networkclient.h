#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H
#include <QTcpSocket>
#include <QString>


class NetworkClient
{
private:
    QTcpSocket *socket;
public:
    NetworkClient();
    void connect();
    void sendToServer(QString message);
    QString receiveFromServer();
};

#endif // NETWORKCLIENT_H
