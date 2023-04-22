#define _CRT_SECURE_NO_WARNINGS
#include <ws2tcpip.h>
#include <thread>
#include "Connection_manager.h"
#include"DB.h"

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

void Connection_manager::requests(SOCKET clientSocket)
{
	char buffer[1024] = "";
	bool running = true;
	while (running)
	{
		if (recv(clientSocket, buffer, sizeof(buffer), 0))
		{
			char* copy = (char*)calloc(strlen(buffer), sizeof(char));
			strcpy(copy, buffer);
			char* identity = strtok(buffer, ":");
			char				message[1024] = "";
			copy = copy + strlen(identity) + 1;
			std::cout << "Request received" << std::endl;
			if (strcmp(identity, "LogIn") == 0)
			{
				if (login(copy))
					strcpy(message, "Corect");
				else
					strcpy(message, "Gresit");
				//free(copy);
			}

			int messageLength = strlen(message);
			send(clientSocket, message, messageLength, 0);
		}
		else
		{
			running = false;
			conected_device_sockets.erase(std::remove(conected_device_sockets.begin(), conected_device_sockets.end(), clientSocket), conected_device_sockets.end());
		}
	}
	closesocket(clientSocket);
	//TODO EXCEPTION
}

void Connection_manager::listen_()
{
	SOCKET				clientSock;
	SOCKADDR_IN			clientAddr;
	int					clientAddrSize = sizeof(clientAddr);
	std::cout << "Listening for connections and requests" << std::endl;
	while (true)
	{
		clientSock = accept(server_socket, (SOCKADDR*)&clientAddr, &clientAddrSize);
		if (clientSock != INVALID_SOCKET)
		{
			std::cout << "Client conected" << std::endl;
			conected_device_sockets.push_back(clientSock);
			std::thread requestThread(&Connection_manager::requests,this, clientSock);
			requestThread.detach();
		}
	}
	//TODO exceptions
}


bool Connection_manager::login(char* buffer)
{
	char*			 token = strtok(buffer, ":");
	std::cout << "---------authentication---------\n";
	std::string		username(token);
	std::cout << "Username " << username << std::endl;

	token = strtok(nullptr, ":");
	std::string password(token);

	std::cout << "Password " << password << std::endl;

	if (DB::get_instance()->verify_account(username, password))
	{
		return true;
	}
	return false;
}
