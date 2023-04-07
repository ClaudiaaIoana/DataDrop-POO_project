#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

    bool _checkPassword(QString password, QString ConfirmPassword) const;

private slots:
    void on_SignUpButton_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
