#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QMainWindow>
#include "networkclient.h"
#include "user.h"
#include "appinterface.h"


namespace Ui {
class AddFriend;
}

class AddFriend : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddFriend(User *user,AppInterface *app,QWidget *parent = nullptr);
    ~AddFriend();

private slots:
    void on_AddButton_clicked();

private:
    AppInterface *appInterface;
   // NetworkClient *ManagerNetwork;
    Ui::AddFriend *ui;
    User *myUser;
};

#endif // ADDFRIEND_H
