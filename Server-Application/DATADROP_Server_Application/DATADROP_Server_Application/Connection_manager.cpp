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

std::vector<std::string> Connection_manager::protocol(char* buffer)
{
	std::vector<std::string> segments;
	char*					 token = strtok(buffer, ":");
	
	while (token)
	{
		segments.push_back(std::string(token));
		token = strtok(nullptr, ":");
	}
	return segments;
}

void Connection_manager::requests(SOCKET clientSocket)
{
	
	bool running = true;
	while (running)
	{
		char						buffer[1024] = "";
		int							messageLength;
		char						message[2048];
		std::vector<std::string>	segments;
		if (recv(clientSocket, buffer, sizeof(buffer), 0))
		{
			segments = protocol(buffer);
			std::cout << "Request received" << std::endl;

			if (strcmp(buffer ,"")==0)
				goto Close_socket;

			//LOGIN
			if (segments[0]=="LogIn")
			{
				
				if (login(segments[1],segments[2]))
				{
					strcpy(message, "Corect:");
					std::string			list = this->give_friend_list(segments[1]);
					if (list.empty())
					{
						strcat(message, "FaraPrieteni");
					}
					else
					{
						strcat(message, "CuPrieteni:");
						strcat(message, list.data());
					}
					conected_device_sockets.erase(std::remove(conected_device_sockets.begin(), conected_device_sockets.end(), clientSocket), conected_device_sockets.end());
					conected_users_sockets.push_back(ClientSocket(segments[1], clientSocket));

					messageLength = strlen(message);
					send(clientSocket, message, messageLength, 0);

					Sleep(10);
					send_messages_at_connection(clientSocket, segments[1]);
				}
				else
				{
					strcpy(message, "Gresit");
					messageLength = strlen(message);
					send(clientSocket, message, messageLength, 0);
				}
				
			}

			//REGISTER
			else if (segments[0]=="Register")
			{
				register_(segments[1],segments[2], segments[3]);
			}

			//ADD FRIEND
			else if (segments[0] == "AddFriend")
			{
				if (add_friend(segments[1],segments[2]))
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

			//MESSAGE RECEIVING AND SENDING
			else if (segments[0]=="Mesaj")
			{
				SOCKET receiver = is_connected(segments[2]);
				if (receiver != NULL)
				{

					strcpy(message, "Mesaj:");
					strcat(message, segments[1].c_str());
					strcat(message, ":");
					strcat(message, segments[2].c_str());
					strcat(message, ":");
					strcat(message, segments[3].c_str());
					strcat(message, "\0");

					uint32_t dimension;
					dimension = strlen(message);
					messageLength = strlen(message);

					send(receiver, (char*)&dimension, sizeof(dimension), 0);
					send(receiver, message, messageLength, 0);
				}
				else
				{
					DB::get_instance()->push_waiting_message(segments[1], segments[2], segments[3]);
				}
			}
			else if (segments[0] == "Creare_grup")
			{
				DB::get_instance()->create_group_with_members(segments[1], std::vector<std::string>(segments.begin() + 2, segments.end()));
			}

			buffer[0] = '\0';

		}
		//erasing the socket from memory
		else
		{
			Close_socket:
			running = false;
			if(std::find(this->conected_device_sockets.begin(),this->conected_device_sockets.end(), clientSocket)!=this->conected_device_sockets.end())
					conected_device_sockets.erase(std::remove(conected_device_sockets.begin(), conected_device_sockets.end(), clientSocket), conected_device_sockets.end());
			auto it = std::find(this->conected_users_sockets.begin(), this->conected_users_sockets.end(), clientSocket);
			if(it!=this->conected_users_sockets.end())
					conected_users_sockets.erase(std::remove(conected_users_sockets.begin(), conected_users_sockets.end(), clientSocket), conected_users_sockets.end());
		}
	}
	std::cout << "Connection closed" << std::endl;
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


bool Connection_manager::login(std::string username, std::string password)
{
	std::cout << "---------authentication---------\n";
	std::cout << "Username " << username << std::endl;
	std::cout << "Password " << password << std::endl;

	if (DB::get_instance()->verify_account(username, password))
	{
		return true;
	}
	return false;
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
	if(!friend_list_packet.empty())
		friend_list_packet.pop_back();
	return friend_list_packet;
}

void Connection_manager::register_(std::string email,std::string username, std::string password)
{
	std::cout << "---------register---------\n";
	std::cout << "Email " << email << std::endl;
	std::cout << "Username " << username << std::endl;
	std::cout << "Password " << password << std::endl;

	DB::get_instance()->add_account(username, email, password);
}

bool Connection_manager::add_friend(std::string user1, std::string user2)
{
	std::cout << "---------add friend---------\n";
	std::cout << "User1: " << user1 << std::endl;
	std::cout << "User2 " << user2 << std::endl;

	if (DB::get_instance()->add_friend(user1, user2))
	{
		return true;
	}
	return false;
}

SOCKET Connection_manager::is_connected(std::string receiver)
{
	auto it = std::find(conected_users_sockets.begin(), conected_users_sockets.end(), receiver);
	if (it != conected_users_sockets.end())
	{
		return (*it).getSocket();
	}
	return SOCKET();
}

void Connection_manager::send_messages_at_connection(SOCKET clientSocket, std::string username)
{
	std::vector<std::pair<std::string, std::string>> sender_message;
	int												 messageLength;
	char											 message[2048] = "\0";
	sender_message = DB::get_instance()->pop_waiting_messages(username);

	for (auto it = sender_message.begin(); it != sender_message.end(); it++)
	{
		strcpy(message, "Mesaj:");
		strcat(message, (*it).first.c_str());
		strcat(message, ":");
		strcat(message, username.c_str());
		strcat(message, ":");
		strcat(message, (*it).second.c_str());
		strcat(message, "\0");		

		uint32_t dimension;
		dimension = strlen(message);
		messageLength = strlen(message);

		send(clientSocket, (char*)&dimension, sizeof(dimension), 0);
		send(clientSocket, message, messageLength, 0);
		Sleep(100);
	}
	DB::get_instance()->delete_sent_messages(username);
}


