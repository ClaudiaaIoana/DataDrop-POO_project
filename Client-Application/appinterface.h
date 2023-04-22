#ifndef APPINTERFACE_H
#define APPINTERFACE_H
#include <QMainWindow>
#include "user.h"
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <string>
#include "networkclient.h"


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
    void onButtonClicked();
    void addFriend(QString username);
    ~AppInterface();
private slots:

     void on_AddFriendButton_clicked();

     void on_CreateGroupButton_clicked();

     void on_AttachButton_clicked();

private:
    NetworkClient *ManagerNetwork;
    Ui::AppInterface *ui;
    User *user;
    QList<QPushButton*> FriendsList;
    QLabel *usernameIcon;
    QLabel *usernameLabel;
    QHBoxLayout *topBarArea;
};

#endif // APPINTERFACE_H
