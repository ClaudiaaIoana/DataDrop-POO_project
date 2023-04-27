#include "message.h"

Message::Message()
{

}
Message::Message(QString sender,QString receiver,QString content):
    sender(sender),receiver(receiver),contentMessage(content)

{
}
QString Message::getSender()
{
    return this->sender;
}
QString Message::getReceiver()
{
    return this->receiver;
}
QString Message::getContentMessage()
{
    return this->contentMessage;
}
