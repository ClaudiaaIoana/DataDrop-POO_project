#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include<string>
#include <winsock2.h>
class ClientSocket
{
	std::string			client_username;
	SOCKET				socket;
public:
							ClientSocket(std::string username, SOCKET socket);
							~ClientSocket();
	std::string				getUsername();
	SOCKET					getSocket();
	friend bool				operator==(ClientSocket& sock,std::string client_username);
	friend bool				operator==(ClientSocket& sock, SOCKET client_socket);
};

