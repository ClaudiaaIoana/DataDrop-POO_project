#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "appinterface.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_clientSocket=new QTcpSocket(this);
    _connectToServer();

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::_receiveFromServer()
{
    m_clientSocket->waitForReadyRead();


    QByteArray responseData = m_clientSocket->readAll();
    QString response = QString::fromUtf8(responseData.constData(), responseData.length());

    return response;
}

void MainWindow::_connectToServer()
{
    m_clientSocket->connectToHost("192.168.1.133",quint16(5555));
    m_clientSocket->open(QIODevice::ReadWrite);
    if(m_clientSocket->isOpen())
    {
       statusBar()->showMessage("Connected to server!");
    }
    else
    {
        statusBar()->showMessage("No connected to server!");
    }
}
void MainWindow::_sendToServer(QString message)
{

    qint64 size = sizeof(message);

    if(!message.isEmpty())
    {
        m_clientSocket->write(QString(message).toUtf8(),size);
        m_clientSocket->waitForBytesWritten();
    }
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

       _sendToServer(message);

       QString checkLogger=_receiveFromServer();

       if(checkLogger=="Corect")
       {
            hide();
            AppInterface *app=new AppInterface();
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

