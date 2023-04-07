#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QTcpSocket>
#include <QMainWindow>

namespace Ui {
class SignUp;
}

class SignUp :  public QDialog
{
    Q_OBJECT

public:
     explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

    bool _checkPassword(QString password, QString ConfirmPassword) const;

    void _connect();
    void _sendToServer(QString message);

private slots:

    void on_SignUpButton_clicked();

private:
    Ui::SignUp *ui;
    QTcpSocket *socket;
};

#endif // SIGNUP_H
