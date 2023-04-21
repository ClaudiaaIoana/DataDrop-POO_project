#include "appinterface.h"
#include "ui_appinterface.h"
#include "addfriend.h"
#include <QLineEdit>
#include <QKeyEvent>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QFileDialog>

AppInterface::AppInterface(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::AppInterface)
{
    this->user =new User("andreiungureanu133@yahoo.com","Andrei Ungureanu",
                         {"Caprita Bogdan","Minulescu Daniel","Banica Alex"},
                         {"C112E","Moldovenii","Plutonul2"});

    ui->setupUi(this);

    ui->Search->setPlaceholderText("  Search Friends...");
    ui->TextLineEdit->setPlaceholderText(" Type ");
    ui->sendButton->setVisible(false);
    ui->TextLineEdit->setVisible(false);
    ui->AttachButton->setVisible(false);

    this->topBarArea=nullptr;
    this->usernameLabel=nullptr;
    this->usernameIcon=nullptr;

    connect(ui->Search, &QLineEdit::textChanged, this, &AppInterface::onSearchEnterPressed);

    setScrollZone();

    for (QPushButton *button : FriendsList)
    {
            connect(button, &QPushButton::clicked, this, &AppInterface::onButtonClicked);     
    }

}

void AppInterface::setScrollArea(QScrollArea *scrollzone)
{
    scrollzone->setWidgetResizable(true);
    scrollzone->setFixedSize(271,470);
    QString scrollBarStyle = "QScrollBar:vertical {"
                             "background-color: #F4F4F4;"
                             "width: 12px;"
                             "margin: 0px;"
                             "}"
                             "QScrollBar::handle:vertical {"
                             "background-color: #DADADA;"
                             "min-height: 20px;"
                             "border-radius: 5px;"
                             "}"
                             "QScrollBar::handle:hover:vertical {"
                             "background-color: #C1C1C1;"
                             "}"
                             "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,"
                             "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                             "background-color: #F4F4F4;"
                             "}";
    scrollzone->verticalScrollBar()->setStyleSheet(scrollBarStyle);

}

void AppInterface::setScrollZone()
{
    QScrollArea *scrollArea = new QScrollArea(ui->ScrollZone);

    setScrollArea(scrollArea);

    QWidget *scrollWidget = new QWidget(scrollArea);
    scrollWidget->setGeometry(100, 450, ui->centralwidget->width(), ui->centralwidget->height() * 0.8);
    scrollArea->setWidget(scrollWidget);

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);

    scrollLayout->setAlignment(Qt::AlignTop);

    QList<QPushButton*> buttonList;

    for (int i = 1; i <= 100; ++i) {
            QPushButton *button = new QPushButton(QString("Utilizator %1").arg(i));
            QIcon icon(":/man_person.png"); // încărcați imaginea utilizatorului dintr-un fișier
            button->setIcon(icon);
            button->setIconSize(QSize(32, 32));
            button->setStyleSheet("QPushButton {"
                                      "border: none;"
                                      "background-color: transparent;"
                                      "color: #1E90FF;"
                                      "padding: 8px 16px;"
                                      "font-family: Arial, sans-serif;"
                                      "font-size: 14px;"
                                      "font-weight: bold;"
                                      "text-align: left;"
                                      "text-transform: none;"
                                      "border-radius: 12px;"
                                  "}"
                                  "QPushButton:hover {"
                                      "background-color: rgba(0, 0, 0, 0.05);"
                                  "}"
                                  "QPushButton:pressed {"
                                      "background-color: rgba(0, 0, 0, 0.1);"
                                  "}");
             buttonList.append(button);
        }
    this->FriendsList=buttonList;
    for (QPushButton *button : buttonList) {
          scrollLayout->addWidget(button);
      }
}

void AppInterface::setChatZone(QPushButton *userButton)
{

    if(this->usernameLabel!=nullptr)
    {
        delete this->topBarArea;
        delete this->usernameLabel;
        delete this->usernameIcon;
        usernameLabel=nullptr;
        usernameIcon=nullptr;
    }

    ui->sendButton->setVisible(true);
    ui->TextLineEdit->setVisible(true);
    ui->AttachButton->setVisible(true);
    ui->TextLineEdit->setText("");

    this->topBarArea = new QHBoxLayout(ui->ChatZone);


    this->usernameLabel=new QLabel();
    this->usernameIcon=new QLabel();

    QPixmap pixmap(":/man_person.png");
    QPixmap scaledPixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio);
    usernameIcon->setPixmap(scaledPixmap);



    usernameLabel->setFixedSize(450, 40);
    usernameLabel->setStyleSheet("background-color: rgb(240, 240, 240);"
                                 "border: 2px solid rgb(211, 211, 211);"
                                 "color: #007FFF;"
                                 "border-radius: 12px;"
                                 "padding: 10px;"
                                 "font-size: 16px;"
                                 );
    usernameLabel->setText(userButton->text());
    topBarArea->addWidget(usernameIcon);
    topBarArea->addWidget(usernameLabel);

    topBarArea->addStretch();

    topBarArea->setAlignment(usernameLabel, Qt::AlignTop);
    topBarArea->setAlignment(usernameIcon, Qt::AlignTop);

}

void AppInterface::onSearchEnterPressed()
{

    QString searchText = ui->Search->text();

    for (QPushButton *button : FriendsList) {
           QString buttonText = button->text();

           if (buttonText.contains(searchText, Qt::CaseInsensitive))
           {
               button->setVisible(true);
           }
           else
           {
               button->setVisible(false);
           }
       }

}

void AppInterface::onButtonClicked()
{

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    setChatZone(button);



}

AppInterface::~AppInterface()
{
    delete ui;
}


void AppInterface::on_AddFriendButton_clicked()
{
      AddFriend *addFriendWindow =new AddFriend();
      addFriendWindow->show();
}


void AppInterface::on_CreateGroupButton_clicked()
{

}


void AppInterface::on_AttachButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Selectați un fișier", "", "Toate fișierele (*.*)");
    if (!file_path.isEmpty())
    {
         ui->TextLineEdit->setText(file_path);
    }
}

