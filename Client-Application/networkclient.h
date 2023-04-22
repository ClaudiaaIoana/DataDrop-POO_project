#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H
#include <QTcpSocket>
#include <QString>


class NetworkClient
{
private:
    static NetworkClient *instance;
    QTcpSocket *socket;
<<<<<<< Updated upstream
    NetworkClient();

public:
    static NetworkClient* getInstance();
    void connect(const QString& host, quint16 port);
    void sendToServer(const QString& message);
=======
    static NetworkClient* instance;
    NetworkClient();
public:
    static NetworkClient* getInstance();
    void connect(const QString& host, quint16 port);
    void sendToServer(const QString message);
>>>>>>> Stashed changes
    QString receiveFromServer();
};

#endif // NETWORKCLIENT_H
