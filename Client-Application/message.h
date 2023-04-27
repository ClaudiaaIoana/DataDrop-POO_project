#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>

class Message
{
private:
    QString sender;
    QString receiver;
    QString contentMessage;
public:
    Message(QString sender,QString receiver,QString content);
    Message();
    QString getSender();
    QString getReceiver();
    QString getContentMessage();
};

#endif // MESSAGE_H
