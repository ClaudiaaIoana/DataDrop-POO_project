#define _CRT_SECURE_NO_WARNINGS
#include "Connection_manager.h"

Connection_manager* Connection_manager::instance = nullptr;

Connection_manager::Connection_manager()
{
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server_socket= socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5555);

	bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address));
	server_address.sin_port = htons(5555);
	listen(server_socket, 50);
}

Connection_manager* Connection_manager::get_instance()
{
	if(instance==nullptr)
		instance = new Connection_manager();
	return instance;
}

void Connection_manager::destroy_instance()
{
	if (instance)
		delete instance;
}

void Connection_manager::acceptConnection()
{
	SOCKET				clientSock;
	SOCKADDR_IN			clientAddr;
	int					clientAddrSize = sizeof(clientAddr);
	clientSock = accept(server_socket, (SOCKADDR*)&clientAddr, &clientAddrSize);
	if (clientSock != INVALID_SOCKET)
	{
		conected_device_sockets.push_back(clientSock);
	}
	//TODO exceptions
}

void Connection_manager::listen_()
{
	while (true)
	{
		acceptConnection();
		for (auto sock = conected_device_sockets.begin(); sock != conected_device_sockets.end(); sock++)
		{
			char buffer[1024] = "";
			recv(*sock, buffer, sizeof(buffer), 0);
		}
		for (auto sock = conected_users_sockets.begin(); sock != conected_users_sockets.end(); sock++)
		{

		}
	}
}


bool Connection_manager::login(char* buffer)
{

	char*			token = strtok(buffer, ":");
	std::string		 identity;
	identity = token;

	if (identity == "LogIn")
	{
		std::cout << "---------authentication---------\n";

		token = strtok(nullptr, ":");
		std::string username(token);
		std::cout << "Username " << username << std::endl;

		token = strtok(nullptr, ":");
		std::string password(token);

		std::cout << "Password " << password << std::endl;
		return true;

	}
}
