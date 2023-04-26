#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H
#include <QTcpSocket>
#include <QString>
#include <QMutex>

class NetworkClient
{
private:
    static NetworkClient *instance;
    QTcpSocket *socket;
    QMutex *mutex;
    NetworkClient();
public:
    static NetworkClient* getInstance();
    void connect(const QString& host, quint16 port);
    void sendToServer(const QString message);
    void sendFile(const QString &filePath);
    QString receiveFromServer();
    QTcpSocket *getSocket();
    QMutex * getMutex();
};

#endif // NETWORKCLIENT_H
