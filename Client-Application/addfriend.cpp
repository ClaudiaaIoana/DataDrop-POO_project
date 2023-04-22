#include "addfriend.h"
#include "ui_addfriend.h"

AddFriend::AddFriend(User *user,AppInterface *app,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    this->appInterface=app;
    this->myUser=user;
    ui->lineUser->setPlaceholderText("  Type...");
   // this->ManagerNetwork=new NetworkClient();
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

   // this->ManagerNetwork->connect();
    //this->ManagerNetwork->sendToServer(message);

   // QString response=this->ManagerNetwork->receiveFromServer();
    //if(response== "Adaugat")
    //{
     //   hide();
       // this->appInterface->addFriend(username);
        //appInterface->show();
    //}
}

