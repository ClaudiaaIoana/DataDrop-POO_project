#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>

class ServerListener : public QObject
{
    Q_OBJECT
public:
    void startListening();
    static ServerListener *getInstanta();
    void setMutexLock();
public slots:
    void sendData(const QByteArray& data);
private:
    static ServerListener *instanta;
    ServerListener(QObject *parent = nullptr);
    QTcpSocket *socket;
    QMutex *mutex;
};

#endif // SERVERLISTENER_H
