/********************************************************************************
** Form generated from reading UI file 'addfriend.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIEND_H
#define UI_ADDFRIEND_H

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

class Ui_AddFriend
{
public:
    QWidget *centralwidget;
    QLineEdit *lineUser;
    QLabel *label;
    QPushButton *AddButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AddFriend)
    {
        if (AddFriend->objectName().isEmpty())
            AddFriend->setObjectName("AddFriend");
        AddFriend->resize(412, 289);
        AddFriend->setMaximumSize(QSize(412, 292));
        AddFriend->setStyleSheet(QString::fromUtf8("background-color: rgb(220, 220, 220);"));
        centralwidget = new QWidget(AddFriend);
        centralwidget->setObjectName("centralwidget");
        lineUser = new QLineEdit(centralwidget);
        lineUser->setObjectName("lineUser");
        lineUser->setGeometry(QRect(140, 100, 141, 28));
        lineUser->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"font: italic 9pt \"Segoe UI\";\n"
"background-color: rgb(255,255,255);\n"
"color:	dark; \n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 40, 171, 31));
        label->setStyleSheet(QString::fromUtf8("background-color:transparent; \n"
"font: 700 18pt \"Segoe UI\";\n"
"background:none; \n"
"border:none ; \n"
"color:black;"));
        AddButton = new QPushButton(centralwidget);
        AddButton->setObjectName("AddButton");
        AddButton->setGeometry(QRect(170, 150, 83, 29));
        QFont font;
        font.setBold(true);
        AddButton->setFont(font);
        AddButton->setStyleSheet(QString::fromUtf8("#AddButton {\n"
"  background-color: white; \n"
"  color: black; \n"
"  border: 2px solid #4CAF50;\n"
"}\n"
"\n"
"#AddButton:hover {\n"
"  background-color: #4CAF50;\n"
"  color: white;\n"
"}"));
        AddFriend->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AddFriend);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 412, 25));
        AddFriend->setMenuBar(menubar);
        statusbar = new QStatusBar(AddFriend);
        statusbar->setObjectName("statusbar");
        AddFriend->setStatusBar(statusbar);

        retranslateUi(AddFriend);

        QMetaObject::connectSlotsByName(AddFriend);
    } // setupUi

    void retranslateUi(QMainWindow *AddFriend)
    {
        AddFriend->setWindowTitle(QCoreApplication::translate("AddFriend", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("AddFriend", "Username", nullptr));
        AddButton->setText(QCoreApplication::translate("AddFriend", "AddFriend", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriend: public Ui_AddFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIEND_H
