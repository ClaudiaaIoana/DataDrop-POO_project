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
	std::vector<std::string>	protocol(char* buffer);
	void						requests(SOCKET clientSocket);
	bool						login(std::string username, std::string password);
	std::string					give_friend_list(std::string username);
	void						register_(std::string email, std::string username, std::string password);
	bool						add_friend(std::string user1, std::string user2);
	SOCKET						is_connected(std::string receiver);
public:
	static						Connection_manager* get_instance();
	static						void destroy_instance();
	void						listen_();
};

