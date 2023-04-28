#include "appinterface.h"
#include "ui_appinterface.h"
#include "addfriend.h"
#include "serverlistener.h"
#include <QLineEdit>
#include <QKeyEvent>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QFileDialog>
#include <QtEndian>
#include <QStandardItemModel>
#include <QScroller>


AppInterface::AppInterface(User *user,QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::AppInterface)
{
    ui->setupUi(this);

    this->user=user;
    this->ManagerNetwork=NetworkClient::getInstance();
    this->socket=ManagerNetwork->getSocket();
    setInterface();
}


void AppInterface::setInterface()
{
    QString labelText="Salut, "+QString::fromStdString(user->_getUsername())+"!";

    ui->labelText->setText(labelText);
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

    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
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

    for (int i = 0; i < this->user->_getSizeFriendBuffer(); ++i) {
            QString usernameIndexName=QString::fromStdString(user->_getUsernameIndex(i));
            QPushButton *button = new QPushButton(usernameIndexName);
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
            button->setProperty("tipButon", "persoana");
            buttonList.append(button);
        }
    for (int i = 0; i < this->user->_getSizeGroups(); ++i) {
            QString GroupIndexName=QString::fromStdString(user->_getGroupIndex(i));
            QPushButton *button = new QPushButton(GroupIndexName);
            QIcon icon(":/teamwork.png");
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
            button->setProperty("tipButon", "grup");
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

    if(userButton->property("tipButon").toString()=="persoana")
    {

    QPixmap pixmap(":/man_person.png");
    QPixmap scaledPixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio);
    usernameIcon->setPixmap(scaledPixmap);

    }
    else if(userButton->property("tipButon").toString() == "grup")
    {
        QPixmap pixmap(":/teamwork.png");
        QPixmap scaledPixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio);
        usernameIcon->setPixmap(scaledPixmap);
    }
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



void AppInterface::setMessages()
{
        ui->listaMesaje->clear();

            for(int i=0; i<messages.size(); i++)
            {
                if(messages[i]->getSender() == usernameLabel->text() && messages[i]->getReceiver() == QString::fromStdString(user->_getUsername()))
                {
                    QListWidgetItem *message = new QListWidgetItem(messages[i]->getContentMessage());
                    QPixmap image(":/man_person.png");
                    QFont font;
                    font.setPointSize(12);
                    message->setFont(font);
                    QPixmap scaledImage = image.scaled(QSize(50, 50));
                    message->setIcon(QIcon(scaledImage));
                    message->setTextAlignment(Qt::AlignLeft);
                    ui->listaMesaje->addItem(message);
                }
                if(messages[i]->getSender() == QString::fromStdString(user->_getUsername()) && messages[i]->getReceiver() == usernameLabel->text())
                {
                    QListWidgetItem *message = new QListWidgetItem(messages[i]->getContentMessage());
                    message->setTextAlignment(Qt::AlignRight);
                    QFont font;
                    font.setPointSize(12);
                    message->setFont(font);
                    ui->listaMesaje->addItem(message);
                }
            }

            ui->listaMesaje->scrollToBottom();
}



 void AppInterface::addFriend(QString username)
 {
     this->user->_addFriend(username);
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
    setMessages();

}

AppInterface::~AppInterface()
{
    delete ui;
}


void AppInterface::on_AddFriendButton_clicked()
{
    hide();
    AddFriend *addFriendWindow =new AddFriend(user,this);
    addFriendWindow->show();
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}


void AppInterface::on_CreateGroupButton_clicked()
{

}


void AppInterface::on_AttachButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Selectați un fișier", "", "Toate fișierele (*.*)");
    if (!file_path.isEmpty())
    {

    }
}

QString AppInterface::getPushFromServer()
{
    QByteArray Data = socket->read(sizeof(uint32_t));
    quint32 result=qFromLittleEndian<quint32>(Data.constData());
    qDebug() << "S-a primit numarul de octeti: "<<result<<"\n";
    QByteArray data=socket->read(result);
    qDebug() << "S-a primit raspunsul: "<<data<<"\n";
    return QString::fromUtf8(data);
}

void AppInterface::onReadyRead()
{
    bool modify=false;
    while(socket->bytesAvailable()>sizeof(quint32))
    {
        QString dataFromServer = getPushFromServer();
        if(dataFromServer=="fisier")
        {
            QString proba = getPushFromServer();
            qDebug()<<"S-a primit fisierul"<<proba;
            //TODO
        }
        else
        {
            QStringList tokens=dataFromServer.split(':');
            if(tokens[0]== "Mesaj")
            {
                Message *newMessage= new Message(tokens[1],tokens[2],tokens[3]);
                this->messages.append(newMessage);
                if( usernameLabel !=nullptr)
                    setMessages();

            }
        }
    }

}

void AppInterface::on_sendButton_clicked()
{

    QString newMessage=ui->TextLineEdit->text();
    QString username=QString::fromStdString(this->user->_getUsername());
    QString usernameToSend=this->usernameLabel->text();
    QString message="Mesaj:" +username+":"+usernameToSend+":"+newMessage;
    if(!newMessage.isEmpty())
    {
        socket->write(QString(message).toUtf8());
        socket->waitForBytesWritten();
        qDebug()<<"S-a trimis mesajul:"<<message;
        Message *message =new Message(username,usernameToSend,newMessage);
        messages.append(message);
        ui->TextLineEdit->setText("");
        setMessages();
    }

}



