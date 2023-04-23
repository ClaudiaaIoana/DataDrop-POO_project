#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "appinterface.h"
#include "networkclient.h"
#include <QStringView>
#include <QStringTokenizer>
#include <QtCore>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->NetworkManager=NetworkClient::getInstance();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonLogIn_clicked()
{
   QString username=ui->UsernameLineEdit->text();
   QString password=ui->PasswordLineEdit->text();

   if(username.isEmpty() or password.isEmpty())
   {
       QMessageBox::warning(this,"Warning","The field is empty!");
   }
   else
   {
       QString message="LogIn:"+username+":"+password;

       this->NetworkManager->sendToServer(message);
       QString checkLoggerAndFriendsList=this->NetworkManager->receiveFromServer();
       QStringList tokens = checkLoggerAndFriendsList.split(':');
       if(tokens[0] == "Corect")
       {
            hide();
            User *user = new User(username.toStdString());
            if(tokens[1] == "CuPrieteni")
            {
                for (auto it = std::next(tokens.begin(), 2); it != tokens.end(); ++it)
                    {
                      user->_addFriend(QString::fromStdString((*it).toStdString()));
                    }
            }
            else if(tokens[1]=="FaraPrieteni")
            {
                user->_clearFriendsList();
            }

            AppInterface *app=new AppInterface(user);
            app->show();
       }
       else
       {
             QMessageBox::warning(this,"Warning","Username or Password is incorrect");
             ui->UsernameLineEdit->setText("");
             ui->PasswordLineEdit->setText("");
       }
   }

}


void MainWindow::on_ButtonSignUp_clicked()
{
    hide();
    this->SignUpWindow=new SignUp();
    SignUpWindow->show();

}


void MainWindow::on_UsernameLineEdit_returnPressed()
{
    ui->PasswordLineEdit->setFocus();
}


void MainWindow::on_SeePassword_pressed()
{

    if(ui->PasswordLineEdit->echoMode() == QLineEdit::Password)
    {
         ui->PasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
         ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
}

