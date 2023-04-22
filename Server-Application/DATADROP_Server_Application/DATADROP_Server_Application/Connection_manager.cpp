#define _CRT_SECURE_NO_WARNINGS
#include <ws2tcpip.h>
#include <thread>
#include "Connection_manager.h"
#include"DB.h"
#include"ClientSocket.h"

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
	
	bool running = true;
	while (running)
	{
		char buffer[1024] = "";
		int messageLength;
		if (recv(clientSocket, buffer, sizeof(buffer), 0))
		{
			char* copy = (char*)calloc(strlen(buffer), sizeof(char));
			strcpy(copy, buffer);
			char* identity = strtok(buffer, ":");
			char				message[1024] = "";
			copy = copy + strlen(identity) + 1;

			std::cout << "Request received" << std::endl;


			//LOGIN
			if (strcmp(identity, "LogIn") == 0)
			{
				std::string		username;
				username = login(copy);
				if (!username.empty())
					strcpy(message, "Corect");
				else
					strcpy(message, "Gresit");

				messageLength = strlen(message);
				send(clientSocket, message, messageLength, 0);

				if (strcmp(message,"Corect")==0)
				{
					std::string			list = this->give_friend_list(username);
					strcpy(message,list.data());
					messageLength = strlen(message);
					send(clientSocket, message, messageLength, 0);
					conected_device_sockets.erase(std::remove(conected_device_sockets.begin(), conected_device_sockets.end(), clientSocket), conected_device_sockets.end());
					conected_users_sockets.push_back(ClientSocket(username, clientSocket));
				}
				
			}

			//REGISTER
			else if (strcmp(identity, "Register") == 0)
			{
				register_(copy);
			}

			//ADD FRIEND
			else if (strcmp(identity, "AddFriend") == 0)
			{
				if (add_friend(copy))
				{
					strcpy(message, "Adaugat");
				}
				else
				{
					strcpy(message, "Respins");
				}
				messageLength = strlen(message);
				send(clientSocket, message, messageLength, 0);
			}

			buffer[0] = '\0';

		}
		//erasing the socket from memory
		else
		{
			running = false;
			if(std::find(this->conected_device_sockets.begin(),this->conected_device_sockets.end(), clientSocket)!=this->conected_device_sockets.end())
					conected_device_sockets.erase(std::remove(conected_device_sockets.begin(), conected_device_sockets.end(), clientSocket), conected_device_sockets.end());
			auto it = std::find(this->conected_users_sockets.begin(), this->conected_users_sockets.end(), clientSocket);
			if(it!=this->conected_users_sockets.end())
					conected_users_sockets.erase(std::remove(conected_users_sockets.begin(), conected_users_sockets.end(), clientSocket), conected_users_sockets.end());
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


std::string Connection_manager::login(char* buffer)
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
		return username;
	}
	return std::string();
}

std::string Connection_manager::give_friend_list(std::string username)
{
	std::string					friend_list_packet;

	std::vector<std::string>	friend_list;
	friend_list = DB::get_instance()->get_friend_list(username);
	for (auto friend_ = friend_list.begin(); friend_ != friend_list.end(); friend_++ , friend_list_packet+=":")
	{
		friend_list_packet += *friend_;
	}
	friend_list_packet.pop_back();
	return friend_list_packet;
}

void Connection_manager::register_(char* buffer)
{

	char*				token = strtok(buffer, ":");
	std::string			email(token);

	std::cout << "---------register---------\n";

	std::cout << "Email " << email << std::endl;

	token = strtok(nullptr, ":");
	std::string username(token);
	std::cout << "Username " << username << std::endl;

	token = strtok(nullptr, ":");
	std::string password(token);
	std::cout << "Password " << password << std::endl;


	DB::get_instance()->add_account(username, email, password);
}

bool Connection_manager::add_friend(char* buffer)
{
	char* token = strtok(buffer, ":");
	std::string			user1(token);
	token = strtok(nullptr, ":");
	std::string			user2(token);

	std::cout << "---------add friend---------\n";

	std::cout << "User1: " << user1 << std::endl;
	std::cout << "User2 " << user2 << std::endl;

	if (DB::get_instance()->add_friend(user1, user2))
	{
		return true;
	}
	return false;
}
