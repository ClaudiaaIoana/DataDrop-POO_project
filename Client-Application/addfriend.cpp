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
    this->socket=ManagerNetwork->getSocket();
    //connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
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

    if(!message.isEmpty())
    {
        socket->write(QString(message).toUtf8());
        socket->waitForBytesWritten();
        qDebug()<<"S-a trimis mesajul:"<<message;
    }
    //this->ManagerNetwork->sendToServer(message);
    //_sleep(1000);
    QString response= ManagerNetwork->receiveFromServer();
    if(response== "Adaugat")
    {
    hide();
    this->myUser->_addFriend(username);
    AppInterface *newApp=this->appInterface;
    newApp->show();
    }
    if(response == "Respins")
    {
         QMessageBox::warning(this,"Warning","The field is empty!");
         ui->lineUser->setText("");
    }
}

