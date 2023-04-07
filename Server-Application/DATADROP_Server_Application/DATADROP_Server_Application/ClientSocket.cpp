#include "ClientSocket.h"

ClientSocket::ClientSocket(std::string username, SOCKET socket)
{
}

ClientSocket::~ClientSocket()
{
}

std::string ClientSocket::getUsername()
{
    return std::string();
}

ClientSocket ClientSocket::operator==(std::string client_username)
{
   // return ClientSocket();
}

ClientSocket ClientSocket::operator==(SOCKET socket)
{
    //return ClientSocket();
}
