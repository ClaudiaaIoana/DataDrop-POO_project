/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *ButtonSignUp;
    QLabel *LogInLabel;
    QLabel *UsernameLabel;
    QLineEdit *UsernameLineEdit;
    QLabel *PasswordLabel;
    QLineEdit *PasswordLineEdit;
    QPushButton *ButtonLogIn;
    QWidget *widget;
    QWidget *widget_2;
    QPushButton *SeePassword;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 650);
        MainWindow->setMaximumSize(QSize(900, 650));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(10);
        font.setBold(false);
        MainWindow->setFont(font);
        MainWindow->setToolTipDuration(1);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/backgr.jpg);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ButtonSignUp = new QPushButton(centralwidget);
        ButtonSignUp->setObjectName("ButtonSignUp");
        ButtonSignUp->setGeometry(QRect(410, 390, 83, 29));
        ButtonSignUp->setStyleSheet(QString::fromUtf8("#ButtonSignUp{\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(23, 37, 104, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border:none ; \n"
"color:white;\n"
"font: 10pt \"Segoe UI\";\n"
"border-radius: 8px;\n"
"} \n"
"#ButtonSignUp:hover{ \n"
"	font: 700 9pt \"Segoe UI\";\n"
"border-radius: 12px;\n"
"}"));
        LogInLabel = new QLabel(centralwidget);
        LogInLabel->setObjectName("LogInLabel");
        LogInLabel->setGeometry(QRect(400, 50, 101, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        LogInLabel->setFont(font1);
        LogInLabel->setStyleSheet(QString::fromUtf8("#LogInLabel{\n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"\n"
"}"));
        UsernameLabel = new QLabel(centralwidget);
        UsernameLabel->setObjectName("UsernameLabel");
        UsernameLabel->setGeometry(QRect(310, 130, 283, 23));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(true);
        UsernameLabel->setFont(font2);
        UsernameLabel->setStyleSheet(QString::fromUtf8("#UsernameLabel{ \n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"}"));
        UsernameLineEdit = new QLineEdit(centralwidget);
        UsernameLineEdit->setObjectName("UsernameLineEdit");
        UsernameLineEdit->setGeometry(QRect(310, 160, 283, 30));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setItalic(true);
        UsernameLineEdit->setFont(font3);
        UsernameLineEdit->setStyleSheet(QString::fromUtf8("#UsernameLineEdit{ \n"
"background-color:transparent; \n"
"color: white;\n"
"border:none; \n"
"border-radius:12px; \n"
"	\n"
"	font: 700 italic 9pt \"Segoe UI\";\n"
"\n"
"}"));
        PasswordLabel = new QLabel(centralwidget);
        PasswordLabel->setObjectName("PasswordLabel");
        PasswordLabel->setGeometry(QRect(310, 190, 285, 48));
        PasswordLabel->setFont(font2);
        PasswordLabel->setStyleSheet(QString::fromUtf8("#PasswordLabel{ \n"
"background-color:transparent; \n"
"background:none; \n"
"border:none ; \n"
"color:white;\n"
"}"));
        PasswordLineEdit = new QLineEdit(centralwidget);
        PasswordLineEdit->setObjectName("PasswordLineEdit");
        PasswordLineEdit->setGeometry(QRect(310, 230, 285, 30));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(10);
        PasswordLineEdit->setFont(font4);
        PasswordLineEdit->setStyleSheet(QString::fromUtf8("#PasswordLineEdit{\n"
"background-color:transparent; \n"
"color:white; \n"
"border:none; \n"
"border-radius:12px; \n"
"} "));
        PasswordLineEdit->setEchoMode(QLineEdit::Password);
        ButtonLogIn = new QPushButton(centralwidget);
        ButtonLogIn->setObjectName("ButtonLogIn");
        ButtonLogIn->setGeometry(QRect(310, 300, 285, 32));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(10);
        font5.setBold(false);
        font5.setItalic(false);
        ButtonLogIn->setFont(font5);
        ButtonLogIn->setToolTipDuration(1);
        ButtonLogIn->setAutoFillBackground(false);
        ButtonLogIn->setStyleSheet(QString::fromUtf8("#ButtonLogIn{\n"
"background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(23, 37, 104, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border:none ; \n"
"color:white;\n"
"font: 10pt \"Segoe UI\";\n"
"border-radius: 8px;\n"
"} \n"
"#ButtonLogIn:hover{ \n"
"	font: 700 9pt \"Segoe UI\";\n"
"border-radius: 12px;\n"
"}\n"
""));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(270, 160, 23, 27));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/User (2).png);"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(270, 230, 23, 31));
        widget_2->setStyleSheet(QString::fromUtf8("background-image: url(:/PadLock (2).png);"));
        SeePassword = new QPushButton(centralwidget);
        SeePassword->setObjectName("SeePassword");
        SeePassword->setGeometry(QRect(600, 230, 34, 31));
        SeePassword->setStyleSheet(QString::fromUtf8("#SeePassword{\n"
"background-image: url(:/see.png); \n"
"background-color:transparent; \n"
"}  \n"
"#SeePassword:pressed{ \n"
" transform: translateY(2px);\n"
"  box-shadow: 0 0 5px rgba(0,0,0,0.4);\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 440, 251, 141));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/LogoImage.png);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 25));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DataDrop", nullptr));
        ButtonSignUp->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        LogInLabel->setText(QCoreApplication::translate("MainWindow", "LogIn", nullptr));
        UsernameLabel->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        UsernameLineEdit->setText(QString());
        UsernameLineEdit->setPlaceholderText(QString());
        PasswordLabel->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        PasswordLineEdit->setText(QString());
        ButtonLogIn->setText(QCoreApplication::translate("MainWindow", "LOGIN", nullptr));
        SeePassword->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
