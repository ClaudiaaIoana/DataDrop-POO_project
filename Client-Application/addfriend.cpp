#include "addfriend.h"
#include "ui_addfriend.h"
#include <QMessageBox>


AddFriend::AddFriend(User *user,AppInterface *app,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    this->appInterface=app;
    this->myUser=user;
    ui->lineUser->setPlaceholderText("  Type...");
    this->ManagerNetwork=NetworkClient::getInstance();
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::on_AddButton_clicked()
{
    QString username=ui->lineUser->text();
    QString myUsername=QString::fromStdString(myUser->_getUsername());
    QString message="AddFriend:"+myUsername+":"+username;

    this->ManagerNetwork->sendToServer(message);

    QString response=this->ManagerNetwork->receiveFromServer();
    if(response== "Adaugat")
    {
    hide();
    this->myUser->_addFriend(username);
    AppInterface *newApp=new AppInterface(myUser);
    newApp->show();
    }
    if(response == "Respins")
    {
         QMessageBox::warning(this,"Warning","The field is empty!");
         ui->lineUser->setText("");
    }
}

