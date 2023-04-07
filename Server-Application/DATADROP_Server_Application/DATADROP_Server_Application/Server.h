#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include<vector>
#include<map>
#include <winsock2.h>
#include"ClientSocket.h"
#include"_IServer.h"

class Server:public _IServer
{
private:
	static Server*				instance;
	std::vector<ClientSocket>	conected_users_sockets;
	std::vector<SOCKET>			conected_device_sockets;
	SOCKET						server_socket;
	SOCKADDR_IN					server_address;
	WSADATA						WSAData;
private:
	Server();
	~Server() = default;
public:
	static Server* get_instance();
	static void destroy_instance();
	void listen_();
	void send();
	void acceptConnection();
};

