#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "signup.h"

#include <QMainWindow>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);



    ~MainWindow();

private slots:
    QString _receiveFromServer();

    void _connectToServer();

    void _sendToServer(QString message);

    void on_ButtonLogIn_clicked();

    void on_ButtonSignUp_clicked();

    void on_UsernameLineEdit_returnPressed();

    void on_SeePassword_pressed();

private:
    Ui::MainWindow *ui;
    SignUp *SignUpWindow;
    QTcpSocket *m_clientSocket;

};
#endif // MAINWINDOW_H
