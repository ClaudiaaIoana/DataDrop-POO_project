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
#include <QtEndian>
#include <QStandardItemModel>
#include <QScroller>
#include <QtGlobal>

#define CHUNK_SIZE 12288

AppInterface::AppInterface(User *user,QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::AppInterface)
{
    ui->setupUi(this);


    this->user=user;
    this->ManagerNetwork=NetworkClient::getInstance();
    this->socket=ManagerNetwork->getSocket();
    ui->CreateGrup_2->hide();
    setInterface();
}

AppInterface::AppInterface(User *user,QList<Message*> messages,QWidget *parent):
    QMainWindow(parent),messages(messages),
    ui(new Ui::AppInterface)
{
    ui->setupUi(this);

    this->user=user;
    this->ManagerNetwork=NetworkClient::getInstance();
    this->socket=ManagerNetwork->getSocket();
    ui->CreateGrup_2->hide();
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
    setScrollZone();

    for (QPushButton *button : FriendsList){
            connect(button, &QPushButton::clicked, this, &AppInterface::onButtonClicked);
    }
    connect(ui->Search, &QLineEdit::textChanged, this, &AppInterface::onSearchEnterPressed);
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(ui->TextLineEdit, &QLineEdit::returnPressed, this, &AppInterface::on_sendButton_clicked);
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
       ui->listaMesaje->setFixedSize(441, 401);
       ui->listaMesaje->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
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
       ui->listaMesaje->verticalScrollBar()->setStyleSheet(scrollBarStyle);
       ui->listaMesaje->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

            ui->listaMesaje->scrollToBottom(); // deruleaza lista la ultimul element

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

    QScrollArea *scrollArea = new QScrollArea(ui->CreateGroupScroll);
    setScrollArea(scrollArea);
    QWidget *scrollWidget = new QWidget(scrollArea);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);

    scrollWidget->setMinimumSize(ui->centralwidget->width(), ui->centralwidget->height() * 0.8);
    scrollLayout->setAlignment(Qt::AlignTop);

    QList<QPushButton*> buttonList;

    for (int i = 0; i < this->user->_getSizeFriendBuffer(); ++i) {
            QString usernameIndexName=QString::fromStdString(user->_getUsernameIndex(i));
            QPushButton *button = new QPushButton(usernameIndexName);
            QIcon icon(":/man_person.png"); // încărcați imaginea utilizatorului dintr-un fișier
            button->setIcon(icon);
            button->setIconSize(QSize(25, 25));
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

    for (QPushButton *button :buttonList)
    {
          scrollLayout->addWidget(button);
    }

    for (QPushButton *button : buttonList)
    {
            connect(button, &QPushButton::clicked, this, &AppInterface::onButtonClickedGroup);
    }
    scrollArea->setWidget(scrollWidget);
    ui->CreateGrup_2->show();
}

void AppInterface::onButtonClickedGroup()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString boxText=ui->label->text();
    if(boxText.isEmpty())
    {
           ui->label->setText(button->text());
    }
    else
    {
        boxText=boxText+","+button->text();
        ui->label->setText(boxText);
    }
}

void AppInterface::on_AttachButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Selectați un fișier", "", "Toate fișierele (*.*)");
    if (!file_path.isEmpty())
    {
          QFile file(file_path);
          if (!file.open(QIODevice::ReadOnly))
          {
              qDebug()<<"Failed to open file";
              return;
          }

          QFileInfo fileInfo(file_path);
          QString fileName = fileInfo.fileName();

          QString ControlMessage="File:";
          ControlMessage=ControlMessage+QString::fromStdString(user->_getUsername())+":"+usernameLabel->text()+":"
                  +fileName+":";

          qint32 fileSize = file.size();
          qDebug() << "File size: " << fileSize;

          ControlMessage=ControlMessage+QString::number(fileSize);

          socket->write(QString(ControlMessage).toUtf8());
          socket->waitForBytesWritten();

          QDataStream out(this->socket);
          out.setVersion(QDataStream::Qt_5_0);

          QByteArray data = file.readAll();
          out.writeRawData(data.constData(), data.size());
          qDebug() << "Sent " << data.size() << " bytes.";

          file.close();
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

    while(socket->bytesAvailable()>sizeof(quint32))
    {
        QString dataFromServer = getPushFromServer();
        QStringList tokens=dataFromServer.split(':');
        if(tokens[0]=="File")
        {
            Message *fileMessage =new Message(tokens[2],tokens[1],tokens[3]);
            qint32 fileSize=tokens[4].toInt();
            int numberOfChunks = 0;
             QByteArray file;

           while (file.size() < fileSize) {
                QByteArray chunk;
                if(this->socket->waitForReadyRead())
                    chunk = socket->read(qMin(qint32(fileSize - file.size()), qint32(CHUNK_SIZE)));

                if (chunk.isEmpty()) {
                    qDebug() << "Eroare la citirea din socket:" << socket->errorString();
                    break;
                }
                file.append(chunk);
                qDebug() << "Numarul de chunk uri" << file.size();
                numberOfChunks++;
            }
            QByteArray chunk= this->socket->read(fileSize-file.size());
            file.append(chunk);
            qDebug() << "Numarul de chunk uri" << file.size();
            qDebug()<<"Numarul de chunker uir"<<file.size();

           QString downloadsDir = QDir::toNativeSeparators(QDir::homePath() + "/Downloads");
           QFile fileWriter(downloadsDir + "/" + tokens[3]);
            if (fileWriter.open(QIODevice::WriteOnly)) {
                fileWriter.write(file);
                fileWriter.close();
                qDebug() << "Fișierul a fost scris cu succes în " << tokens[3];
            } else {
                qDebug() << "Eroare la deschiderea fișierului pentru scriere" << tokens[3];
            }

            this->messages.append(fileMessage);
            if( usernameLabel !=nullptr)
                setMessages();
            qDebug() << "S-a primit fișierul" << tokens[3];
        }
        else if(tokens[0]== "Mesaj"){
                Message *newMessage= new Message(tokens[1],tokens[2],tokens[3]);
                this->messages.append(newMessage);
                if( usernameLabel !=nullptr)
                    setMessages();

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




void AppInterface::on_pushButton_clicked()
{
    QString ListMembers=ui->label->text();
    ListMembers.replace(",",":");
    QString GroupName=ui->NameGroup->text();
    QString RequestToGroup="Creare_grup:"+GroupName+":"+ListMembers+":"+QString::fromStdString(user->_getUsername());

    socket->write(RequestToGroup.toUtf8());
    socket->waitForBytesWritten();
    qDebug()<<"S-a trimis mesajul:"<<RequestToGroup;

    user->_addGroup(GroupName);

    ui->CreateGrup_2->hide();

    this->hide();

    AppInterface *newApp=new AppInterface(user);
    newApp->show();

}

