#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include<string>
#include <winsock2.h>
#include"Socket.h"
class ClientSocket:public IVirtualSocket
{
	std::string			client_username;
	SOCKET				socket;
public:
	ClientSocket(std::string username, SOCKET socket);
	~ClientSocket();
	std::string		getUsername();
	ClientSocket	operator==(std::string client_username);
	ClientSocket	operator==(SOCKET socket);
};

