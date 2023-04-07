#include "Server.h"

Server* Server::instance = nullptr;

Server::Server()
{
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server_socket= socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5555);

	bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address));
	server_address.sin_port = htons(5555);
}

Server* Server::get_instance()
{
	if(instance==nullptr)
		instance = new Server();
	return instance;
}

void Server::destroy_instance()
{
	if (instance)
		delete instance;
}

void Server::listen_()
{
	listen(server_socket, 0);
	//while
}
