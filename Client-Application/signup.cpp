#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include "mainwindow.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
   // this->NetworkManager = new NetworkClient();
}

SignUp::~SignUp()
{
    delete ui;
}

bool SignUp::_checkPassword(QString password, QString ConfirmPassword) const
{
    int numberDigit=0;
    int numberUpper=0;

    for(auto it=password.begin();it!=password.end();it++)
    {
        if((*it)>='0' and (*it)<='9')
            numberDigit++;
        if((*it)>='A' and (*it)<='Z')
            numberUpper++;

    }

    if(password.length()<8 or numberDigit == 0 or numberDigit == 0)
        return true;
    return false;
}


void SignUp::on_SignUpButton_clicked()
{
    QString EmailText=ui->EmailLine->text();
    QString UsernameText=ui->UsenameLine->text();
    QString PasswordText=ui->PasswordLine->text();
    QString ConfirmText=ui->ConfirmLine->text();

    bool empty=false;
    bool confirm=false;
    bool checked=false;

    if(EmailText.isEmpty() or UsernameText.isEmpty() or PasswordText.isEmpty() or ConfirmText.isEmpty())
    {
        empty=true;
        QMessageBox::warning(this,"Warning","The field is empty!");
    }


    if(PasswordText != ConfirmText)
    {
        confirm=true;
        QMessageBox::critical(this,"Critical","Password and Confirm Password must be match!");
    }

    if(_checkPassword(PasswordText,ConfirmText) and confirm == false and empty == false)
    {
        checked=true;
        QMessageBox::warning(this,"Warning","The password must contain at least 8 characters including upper/lowercase and numbers!");
    }

    if(empty == false and confirm == false and checked == false)
    {
        QString message="Register:"+EmailText+":"+UsernameText+":"+PasswordText;

<<<<<<< Updated upstream
        //this->NetworkManager->connect();
=======
       // this->NetworkManager->connect();
>>>>>>> Stashed changes
        //this->NetworkManager->sendToServer(message);

        this->hide();
        MainWindow *gotoLog=new MainWindow();
        gotoLog->show();
    }


}


void SignUp::on_BackButton_clicked()
{
    this->hide();
    MainWindow *gotoLog=new MainWindow();
    gotoLog->show();

}

