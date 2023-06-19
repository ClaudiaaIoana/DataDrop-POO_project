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
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
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
    QListWidget *listaMesaje;
    QListWidget *listWidget;
    QLabel *labelText;
    QLineEdit *Search;
    QWidget *ScrollZone;
    QWidget *widget;
    QPushButton *AddFriendButton;
    QPushButton *CreateGroupButton;
    QDockWidget *CreateGrup_2;
    QWidget *dockWidgetContents_6;
    QPlainTextEdit *plainTextEdit;
    QScrollArea *CreateGroupScroll;
    QWidget *scrollAreaWidgetContents;
    QLabel *label;
    QLineEdit *NameGroup;
    QPushButton *pushButton;
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
        ChatZone->setStyleSheet(QString::fromUtf8("image: url(:/qwd83nc4xxf41.jpg);\n"
" background-repeat: no-repeat;\n"
"\n"
"    \n"
"    opacity: 0.8;"));
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
        font.setBold(false);
        font.setItalic(true);
        TextLineEdit->setFont(font);
        TextLineEdit->setStyleSheet(QString::fromUtf8("#TextLineEdit{\n"
"    background-color: white;\n"
"    padding: 5px; \n"
"    font-size: 14px;\n"
"    color: black;\n"
"    outline: none;\n"
"}\n"
"\n"
"#TextLineEdit:hover {\n"
"    border-color: #0078d7;  \n"
"\n"
"}\n"
"\n"
"#TextLineEdit:focus {\n"
"    border-color: #0078d7;\n"
"    box-shadow: 0 0 5px #0078d7;\n"
"   \n"
"}\n"
"  \n"
"    \n"
"    \n"
"\n"
"\n"
" \n"
"\n"
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
        listaMesaje = new QListWidget(ChatZone);
        listaMesaje->setObjectName("listaMesaje");
        listaMesaje->setGeometry(QRect(40, 71, 450, 430));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listaMesaje->sizePolicy().hasHeightForWidth());
        listaMesaje->setSizePolicy(sizePolicy1);
        listaMesaje->setMaximumSize(QSize(450, 430));
        listaMesaje->setFocusPolicy(Qt::NoFocus);
        listaMesaje->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"  border: none;\n"
"  outline: none;"));
        listaMesaje->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listaMesaje->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 120, 271, 461));
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 245);"));
        labelText = new QLabel(centralwidget);
        labelText->setObjectName("labelText");
        labelText->setGeometry(QRect(130, 0, 121, 41));
        labelText->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    color: #1E90FF;\n"
"    font-family: Arial;\n"
"    font-size: 14px;\n"
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
        CreateGrup_2 = new QDockWidget(centralwidget);
        CreateGrup_2->setObjectName("CreateGrup_2");
        CreateGrup_2->setGeometry(QRect(400, 50, 300, 450));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(CreateGrup_2->sizePolicy().hasHeightForWidth());
        CreateGrup_2->setSizePolicy(sizePolicy2);
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName("dockWidgetContents_6");
        plainTextEdit = new QPlainTextEdit(dockWidgetContents_6);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(90, 10, 141, 31));
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    color: #1E90FF;\n"
"    font-family: Arial;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    text-align: center;\n"
"    border: none;"));
        CreateGroupScroll = new QScrollArea(dockWidgetContents_6);
        CreateGroupScroll->setObjectName("CreateGroupScroll");
        CreateGroupScroll->setGeometry(QRect(20, 134, 271, 281));
        CreateGroupScroll->setStyleSheet(QString::fromUtf8("border: none; "));
        CreateGroupScroll->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 271, 281));
        CreateGroupScroll->setWidget(scrollAreaWidgetContents);
        label = new QLabel(dockWidgetContents_6);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 100, 261, 20));
        label->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"font: italic 9pt \"Segoe UI\";\n"
"color:	#1E90FF; \n"
""));
        NameGroup = new QLineEdit(dockWidgetContents_6);
        NameGroup->setObjectName("NameGroup");
        NameGroup->setGeometry(QRect(20, 50, 151, 28));
        NameGroup->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"font: italic 9pt \"Segoe UI\";\n"
"background-color: rgb(245,245,245);\n"
"color:	#1E90FF; "));
        pushButton = new QPushButton(dockWidgetContents_6);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 50, 83, 29));
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton{\n"
"  background-color: white; \n"
"  color: black; \n"
"  border: 2px solid #4CAF50;\n"
"}\n"
"\n"
"#pushButton:hover {\n"
"  background-color: #4CAF50;\n"
"  color: white;\n"
"}"));
        CreateGrup_2->setWidget(dockWidgetContents_6);
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
        labelText->setText(QString());
        AddFriendButton->setText(QString());
        CreateGroupButton->setText(QString());
        plainTextEdit->setPlainText(QCoreApplication::translate("AppInterface", "Create a group", nullptr));
        label->setText(QString());
        NameGroup->setPlaceholderText(QCoreApplication::translate("AppInterface", "    Name Your Group", nullptr));
        pushButton->setText(QCoreApplication::translate("AppInterface", "Finish", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppInterface: public Ui_AppInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPINTERFACE_H
