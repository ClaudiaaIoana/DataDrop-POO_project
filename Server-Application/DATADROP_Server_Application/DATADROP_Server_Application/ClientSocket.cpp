#include "ClientSocket.h"

ClientSocket::ClientSocket(std::string username, SOCKET socket)
{
    this->client_username = username;
    this->socket = socket;
}

ClientSocket::~ClientSocket()
{
}

std::string ClientSocket::getUsername()
{
    return std::string();
}

SOCKET ClientSocket::getSocket()
{
    return socket;
}

bool operator==(ClientSocket& sock, std::string client_username)
{
    if (sock.client_username == client_username)
        return true;
    return false;
}

bool operator==(ClientSocket& sock, SOCKET client_socket)
{
    if (sock.socket == client_socket)
        return true;
    return false;
}
