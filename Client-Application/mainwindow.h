#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "signup.h"
#include <QMainWindow>
#include <QTcpSocket>
#include "networkclient.h"
#include "user.h"


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

    void on_ButtonLogIn_clicked();

    void on_ButtonSignUp_clicked();

    void on_UsernameLineEdit_returnPressed();

    void on_SeePassword_pressed();

private:
    NetworkClient    *NetworkManager;
    Ui::MainWindow   *ui;
    SignUp           *SignUpWindow;
};
#endif // MAINWINDOW_H
