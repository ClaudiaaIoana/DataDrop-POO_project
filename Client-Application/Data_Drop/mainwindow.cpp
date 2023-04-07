#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonLogIn_clicked()
{
    QString username=ui->UsernameLineEdit->text();
    QString password=ui->PasswordLineEdit->text();

    if(username=="Andrei"&&password=="parola")
    {

        hide();

    }
    else
    {

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

