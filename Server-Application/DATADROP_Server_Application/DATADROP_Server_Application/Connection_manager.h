#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include<vector>
#include<map>
#include <winsock2.h>
#include"ClientSocket.h"
#include"_IConnection_manager.h"

class Connection_manager:public _IConnection_manager
{
private:
	static Connection_manager*				instance;
	std::vector<ClientSocket>	conected_users_sockets;
	std::vector<SOCKET>			conected_device_sockets;
	SOCKET						server_socket;
	SOCKADDR_IN					server_address;
	WSADATA						WSAData;
private:
	Connection_manager();
	~Connection_manager() = default;
public:
	static Connection_manager* get_instance();
	static void destroy_instance();
	void listen_();
	void requests(SOCKET clientSocket);
	bool login(char* buffer);
	void register_(char* buffer);
};

