#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QTcpSocket>
#include <QMainWindow>
#include "networkclient.h"


namespace Ui {
class SignUp;
}

class SignUp :  public QDialog
{
    Q_OBJECT

public:
     explicit SignUp(QWidget *parent = nullptr);


    bool _checkPassword(QString password, QString ConfirmPassword) const;
     ~SignUp();
private slots:

    void on_SignUpButton_clicked();

    void on_BackButton_clicked();

private:
    NetworkClient * NetworkManager;
    Ui::SignUp *ui;
    QTcpSocket *socket;
};

#endif // SIGNUP_H
