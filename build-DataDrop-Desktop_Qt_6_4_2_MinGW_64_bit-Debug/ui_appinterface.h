/********************************************************************************
** Form generated from reading UI file 'appinterface.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPINTERFACE_H
#define UI_APPINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppInterface
{
public:
    QWidget *centralwidget;
    QWidget *ChatZone;
    QPushButton *sendButton;
    QLineEdit *TextLineEdit;
    QPushButton *AttachButton;
    QListWidget *listWidget;
    QLabel *label;
    QLineEdit *Search;
    QWidget *ScrollZone;
    QWidget *widget;
    QPushButton *AddFriendButton;
    QPushButton *CreateGroupButton;
    QMenuBar *menubar;

    void setupUi(QMainWindow *AppInterface)
    {
        if (AppInterface->objectName().isEmpty())
            AppInterface->setObjectName("AppInterface");
        AppInterface->resize(800, 580);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AppInterface->sizePolicy().hasHeightForWidth());
        AppInterface->setSizePolicy(sizePolicy);
        AppInterface->setMaximumSize(QSize(800, 580));
        AppInterface->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(AppInterface);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(4, 550));
        centralwidget->setMaximumSize(QSize(800, 650));
        centralwidget->setBaseSize(QSize(800, 550));
        ChatZone = new QWidget(centralwidget);
        ChatZone->setObjectName("ChatZone");
        ChatZone->setGeometry(QRect(270, 0, 551, 791));
        ChatZone->setMaximumSize(QSize(900, 800));
        ChatZone->setStyleSheet(QString::fromUtf8("image: url(:/qwd83nc4xxf41.jpg);"));
        sendButton = new QPushButton(ChatZone);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(470, 505, 31, 31));
        sendButton->setCursor(QCursor(Qt::PointingHandCursor));
        sendButton->setStyleSheet(QString::fromUtf8("\n"
"  image: url(:/send-message.png);  \n"
"background:transparent;\n"
" background-repeat: no; \n"
"  width: 200px;\n"
"  height: 50px;\n"
"  padding: 0;\n"
"  border: none;\n"
"  cursor: pointer; \n"
" display: inline-block;\n"
"\n"
"\n"
""));
        TextLineEdit = new QLineEdit(ChatZone);
        TextLineEdit->setObjectName("TextLineEdit");
        TextLineEdit->setGeometry(QRect(90, 507, 371, 29));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(true);
        TextLineEdit->setFont(font);
        TextLineEdit->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"font: italic 9pt \"Segoe UI\";\n"
"background-color: rgb(255,255,255);\n"
"\n"
" background-repeat: no; \n"
"  width: 200px;\n"
"  height: 50px;\n"
"  padding: 0;\n"
"  border: none;\n"
"  cursor: pointer; \n"
" display: inline-block;\n"
""));
        AttachButton = new QPushButton(ChatZone);
        AttachButton->setObjectName("AttachButton");
        AttachButton->setGeometry(QRect(40, 500, 41, 41));
        AttachButton->setCursor(QCursor(Qt::PointingHandCursor));
        AttachButton->setStyleSheet(QString::fromUtf8("image: url(:/attach.png); \n"
"background:transparent;\n"
" background-repeat: no; \n"
"  width: 200px;\n"
"  height: 50px;\n"
"  padding: 0;\n"
"  border: none;\n"
"  cursor: pointer; \n"
" display: inline-block;"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 120, 271, 461));
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 245);"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 0, 131, 41));
        label->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    color: #1E90FF;\n"
"    font-family: Arial;\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"    text-align: center;\n"
"    border: none;"));
        Search = new QLineEdit(centralwidget);
        Search->setObjectName("Search");
        Search->setGeometry(QRect(10, 90, 251, 28));
        Search->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"font: italic 9pt \"Segoe UI\";\n"
"background-color: rgb(245,245,245);\n"
"color:	#1E90FF; \n"
""));
        ScrollZone = new QWidget(centralwidget);
        ScrollZone->setObjectName("ScrollZone");
        ScrollZone->setGeometry(QRect(0, 120, 271, 461));
        ScrollZone->setStyleSheet(QString::fromUtf8("border: none; "));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 0, 89, 90));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/ChatG.png);"));
        AddFriendButton = new QPushButton(centralwidget);
        AddFriendButton->setObjectName("AddFriendButton");
        AddFriendButton->setGeometry(QRect(220, 40, 41, 41));
        AddFriendButton->setCursor(QCursor(Qt::PointingHandCursor));
        AddFriendButton->setStyleSheet(QString::fromUtf8("background-image: url(:/add-user.png); \n"
"border: none; \n"
"cursor: pointer; \n"
" background-repeat: no;\n"
""));
        CreateGroupButton = new QPushButton(centralwidget);
        CreateGroupButton->setObjectName("CreateGroupButton");
        CreateGroupButton->setGeometry(QRect(160, 40, 51, 41));
        CreateGroupButton->setCursor(QCursor(Qt::PointingHandCursor));
        CreateGroupButton->setStyleSheet(QString::fromUtf8("background-image: url(:/groups.png);\n"
"border: none; \n"
"cursor: pointer; \n"
" background-repeat: no;"));
        AppInterface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AppInterface);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        AppInterface->setMenuBar(menubar);

        retranslateUi(AppInterface);

        QMetaObject::connectSlotsByName(AppInterface);
    } // setupUi

    void retranslateUi(QMainWindow *AppInterface)
    {
        AppInterface->setWindowTitle(QCoreApplication::translate("AppInterface", "MainWindow", nullptr));
        sendButton->setText(QString());
        AttachButton->setText(QString());
        label->setText(QCoreApplication::translate("AppInterface", "       Salut!", nullptr));
        AddFriendButton->setText(QString());
        CreateGroupButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AppInterface: public Ui_AppInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPINTERFACE_H
