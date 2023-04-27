#ifndef APPINTERFACE_H
#define APPINTERFACE_H
#include <QMainWindow>
#include "user.h"
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <string>
#include <QThread>
#include "networkclient.h"
#include "serverlistener.h"
#include <QObject>
#include "message.h"
#include <QListView>
#include <QListWidget>


namespace Ui {
class AppInterface;
}

class AppInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppInterface(User *user,QWidget *parent = nullptr);
    void onSearchEnterPressed();
    void setScrollZone();
    void setChatZone(QPushButton *userButton);
    void setScrollArea(QScrollArea *scrollzone);
    void setInterface();
    void setMessages();
    void onButtonClicked();
    void addFriend(QString username);
    QString getPushFromServer();
    ~AppInterface();
signals:
    void sendData(const QByteArray& data);
public slots:
    void onReadyRead();
private slots:

     void on_AddFriendButton_clicked();

     void on_CreateGroupButton_clicked();

     void on_AttachButton_clicked();

     void on_sendButton_clicked();

private:
    QListWidget *listaMesaje;
    QTcpSocket*socket;
    NetworkClient *ManagerNetwork;
    Ui::AppInterface *ui;
    User *user;
    QList<QPushButton*> FriendsList;
    QList<Message*> messages;
    QLabel *usernameIcon;
    QLabel *usernameLabel;
    QHBoxLayout *topBarArea;
};

#endif // APPINTERFACE_H
