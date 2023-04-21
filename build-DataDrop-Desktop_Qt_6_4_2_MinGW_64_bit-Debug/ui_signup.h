/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QWidget *widget;
    QLabel *Title;
    QLabel *Email;
    QLabel *Username;
    QLabel *Password;
    QLabel *Confirm;
    QLineEdit *EmailLine;
    QLineEdit *UsenameLine;
    QLineEdit *PasswordLine;
    QLineEdit *ConfirmLine;
    QPushButton *SignUpButton;
    QWidget *widget_2;
    QWidget *widget_3;
    QWidget *widget_4;
    QWidget *widget_5;
    QLabel *label;

    void setupUi(QDialog *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(900, 700);
        SignUp->setMinimumSize(QSize(900, 700));
        SignUp->setMaximumSize(QSize(900, 700));
        widget = new QWidget(SignUp);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 901, 711));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/backgr.jpg);"));
        Title = new QLabel(widget);
        Title->setObjectName("Title");
        Title->setGeometry(QRect(350, 80, 291, 71));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        Title->setFont(font);
        Title->setStyleSheet(QString::fromUtf8("#Title{\n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"\n"
"}"));
        Email = new QLabel(widget);
        Email->setObjectName("Email");
        Email->setGeometry(QRect(370, 200, 111, 31));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(true);
        Email->setFont(font1);
        Email->setStyleSheet(QString::fromUtf8("#Email{ \n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"}"));
        Username = new QLabel(widget);
        Username->setObjectName("Username");
        Username->setGeometry(QRect(370, 260, 101, 31));
        Username->setFont(font1);
        Username->setStyleSheet(QString::fromUtf8("#Username{ \n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"}"));
        Password = new QLabel(widget);
        Password->setObjectName("Password");
        Password->setGeometry(QRect(370, 320, 111, 31));
        Password->setFont(font1);
        Password->setStyleSheet(QString::fromUtf8("#Password{ \n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"}"));
        Confirm = new QLabel(widget);
        Confirm->setObjectName("Confirm");
        Confirm->setGeometry(QRect(370, 380, 151, 51));
        Confirm->setFont(font1);
        Confirm->setStyleSheet(QString::fromUtf8("#Confirm{ \n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"}"));
        EmailLine = new QLineEdit(widget);
        EmailLine->setObjectName("EmailLine");
        EmailLine->setGeometry(QRect(370, 230, 211, 31));
        QFont font2;
        font2.setBold(true);
        font2.setItalic(true);
        EmailLine->setFont(font2);
        EmailLine->setStyleSheet(QString::fromUtf8("#EmailLine{ \n"
"background-color:transparent; \n"
"color:white; \n"
"border:none; \n"
"border-radius:12px; \n"
"\n"
"}"));
        UsenameLine = new QLineEdit(widget);
        UsenameLine->setObjectName("UsenameLine");
        UsenameLine->setGeometry(QRect(370, 290, 211, 31));
        UsenameLine->setFont(font2);
        UsenameLine->setStyleSheet(QString::fromUtf8("#UsenameLine{ \n"
"background-color:transparent; \n"
"color:white; \n"
"border:none; \n"
"border-radius:12px; \n"
"\n"
"}"));
        PasswordLine = new QLineEdit(widget);
        PasswordLine->setObjectName("PasswordLine");
        PasswordLine->setGeometry(QRect(370, 350, 211, 31));
        PasswordLine->setFont(font2);
        PasswordLine->setStyleSheet(QString::fromUtf8("#PasswordLine{ \n"
"background-color:transparent; \n"
"color:white; \n"
"border:none; \n"
"border-radius:12px; \n"
"\n"
"}"));
        PasswordLine->setEchoMode(QLineEdit::Password);
        ConfirmLine = new QLineEdit(widget);
        ConfirmLine->setObjectName("ConfirmLine");
        ConfirmLine->setGeometry(QRect(370, 420, 211, 31));
        ConfirmLine->setFont(font2);
        ConfirmLine->setStyleSheet(QString::fromUtf8("#ConfirmLine{ \n"
"background-color:transparent; \n"
"color:white; \n"
"border:none; \n"
"border-radius:12px; \n"
"\n"
"}"));
        ConfirmLine->setEchoMode(QLineEdit::Password);
        SignUpButton = new QPushButton(widget);
        SignUpButton->setObjectName("SignUpButton");
        SignUpButton->setGeometry(QRect(420, 480, 83, 29));
        SignUpButton->setStyleSheet(QString::fromUtf8("#SignUpButton{\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(23, 37, 104, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border:none ; \n"
"color:white;\n"
"font: 10pt \"Segoe UI\";\n"
"border-radius: 8px;\n"
"} \n"
"#SignUpButton:hover{ \n"
"	font: 700 9pt \"Segoe UI\";\n"
"border-radius: 12px;\n"
"}"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(330, 290, 23, 27));
        widget_2->setStyleSheet(QString::fromUtf8("background-image: url(:/User (2).png);"));
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(330, 350, 23, 31));
        widget_3->setStyleSheet(QString::fromUtf8("background-image: url(:/PadLock (2).png);"));
        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(330, 420, 23, 31));
        widget_4->setStyleSheet(QString::fromUtf8("background-image: url(:/PadLock (2).png);"));
        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(330, 230, 31, 23));
        widget_5->setStyleSheet(QString::fromUtf8("background-image: url(:/Email (2).png);"));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(350, 540, 250, 141));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/LogoImage.png); \n"
"background-color:transparent;"));

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QDialog *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "Dialog", nullptr));
        Title->setText(QCoreApplication::translate("SignUp", "Create an account", nullptr));
        Email->setText(QCoreApplication::translate("SignUp", "Email", nullptr));
        Username->setText(QCoreApplication::translate("SignUp", "Username", nullptr));
        Password->setText(QCoreApplication::translate("SignUp", "Password", nullptr));
        Confirm->setText(QCoreApplication::translate("SignUp", "Confirm Password", nullptr));
        SignUpButton->setText(QCoreApplication::translate("SignUp", "SIGN UP", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
