#define _CRT_SECURE_NO_WARNINGS
#define CHUNK_SIZE		1024

#include <ws2tcpip.h>
#include <thread>
#include "Connection_manager.h"
#include"DB.h"
#include"ClientSocket.h"

Connection_manager* Connection_manager::instance = nullptr;


Connection_manager::Connection_manager()
{
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5555);

	bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address));
	server_address.sin_port = htons(5555);
	listen(server_socket, 50);
}

Connection_manager* Connection_manager::get_instance()
{
	if (instance == nullptr)
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
	char* token = strtok(buffer, ":");

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


		recv(clientSocket, buffer, sizeof(buffer), 0);

		segments = protocol(buffer);
		std::cout << "Request received" << std::endl;

		if (strcmp(buffer, ""))
		{

			//LOGIN
			if (segments[0] == "LogIn")
			{

				if (login(segments[1], segments[2]))
				{
					strcpy(message, "Corect:");
					std::string			friend_list = this->give_friend_list(segments[1]);
					if (friend_list.empty())
					{
						strcat(message, "FaraPrieteni");
					}
					else
					{
						strcat(message, "CuPrieteni:");
						strcat(message, friend_list.data());
					}
					messageLength = strlen(message);
					//send(clientSocket, (char*)&messageLength, sizeof(messageLength), 0);
					send(clientSocket, message, messageLength, 0);
					Sleep(50);

					std::string			group_list = this->give_group_list(segments[1]);
					if (group_list.empty())
					{
						strcpy(message, "FaraGrupuri");
					}
					else
					{
						strcpy(message, "CuGrupuri:");
						strcat(message, group_list.data());
					}

					messageLength = strlen(message);
					//send(clientSocket, (char*)&messageLength, sizeof(messageLength), 0);
					send(clientSocket, message, messageLength, 0);
					Sleep(20);

					conected_device_sockets.erase(std::remove(conected_device_sockets.begin(), conected_device_sockets.end(), clientSocket), conected_device_sockets.end());
					conected_users_sockets.push_back(ClientSocket(segments[1], clientSocket));

					Sleep(10);
					send_messages_at_connection(clientSocket, segments[1]);
					Sleep(10);
					send_group_message_at_connection(clientSocket, segments[1]);

					Sleep(10);
					send_files_at_connection(clientSocket, segments[1]);
					Sleep(10);
					send_group_files_at_connection(clientSocket, segments[1]);
				}
				else
				{
					strcpy(message, "Gresit");
					messageLength = strlen(message);
					send(clientSocket, message, messageLength, 0);
				}

			}

			//REGISTER
			else if (segments[0] == "Register")
			{
				register_(segments[1], segments[2], segments[3]);
			}

			//ADD FRIEND
			else if (segments[0] == "AddFriend")
			{
				if (add_friend(segments[1], segments[2]))
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
			else if (segments[0] == "Mesaj")
			{
				SOCKET receiver = is_connected(segments[2]);
				if (receiver != NULL)
				{
					this->send_message_for_connected_user(receiver, segments[1], segments[2], segments[3]);
				}
				else
				{
					DB::get_instance()->push_waiting_message(segments[1], segments[2], segments[3]);
				}
			}

			//FILE RECEIVING AND SENDING
			else if (segments[0] == "File")
			{
				int					dimension = std::stoi(segments[4]);
				char* content = new char[dimension];
				SOCKET				receiver = is_connected(segments[2]);

				memset(content, 0, dimension);

				int					current_size = 0;
				int					bytes_returned = 0;
				while (current_size < dimension)
				{
					Sleep(10);
					bytes_returned = recv(clientSocket, content + current_size, CHUNK_SIZE, 0);
					current_size += bytes_returned;
				}

				File file(segments[1], segments[2], segments[3], dimension);

				if (receiver != NULL)
				{
					std::cout << "SENDING FILE: " << file.get_name() << std::endl;
					this->send_files_for_connected_client(receiver, file, content);

				}
				else
				{
					std::cout << "STORING FILE IN DATABASE: " << file.get_name() << std::endl;
					DB::get_instance()->push_waiting_files(file, content);
				}
				delete content;
			}
			//CREATE GROUP 
			else if (segments[0] == "Creare_grup")
			{
				DB::get_instance()->create_group_with_members(segments[1], std::vector<std::string>(segments.begin() + 2, segments.end()));
			}

			//MESAJ PE GRUP

			else if (segments[0] == "Mesaj_grup")
			{
				std::vector<std::string>		group_members = DB::get_instance()->get_group_members(segments[1], segments[2]);
				bool							pushed = false;
				int								index = 0;

				for (auto it = group_members.begin(); it != group_members.end(); it++)
				{
					SOCKET receiver = is_connected((*it));
					if (receiver != NULL)
					{
						this->send_group_message_for_connected_user(receiver, segments[1], (*it), segments[3]);
					}
					else
					{
						if (!pushed)
						{
							index = DB::get_instance()->push_group_messages(segments[1], segments[2], segments[3]);
							pushed = true;
						}
						DB::get_instance()->push_group_message_for_user(index, (*it));
					}
				}
			}

			//GROUP FILE RECEIVING AND SENDING

			else if (segments[0] == "File_grup")
			{
				int								dimension = std::stoi(segments[4]);
				char*							content = new char[dimension];
				std::vector<std::string>		group_members = DB::get_instance()->get_group_members(segments[1], segments[2]);
				bool							pushed = false;
				int								index = 0;
				int								current_size = 0; 
				int								bytes_returned = 0;

				memset(content, 0, dimension);

				while (current_size < dimension)
				{
					Sleep(10);
					bytes_returned = recv(clientSocket, content + current_size, CHUNK_SIZE, 0);
					current_size += bytes_returned;
				}

				File file(segments[2], segments[1], segments[3], dimension);

				for (auto it = group_members.begin(); it != group_members.end(); it++)
				{
					SOCKET receiver = is_connected((*it));
					if (receiver != NULL)
					{
						this->send_group_files_for_connected_client(receiver, file, (*it), content);
					}
					else
					{
						if (!pushed)
						{
							index = DB::get_instance()->push_waiting_group_files(file, content);
							pushed = true;
						}
						DB::get_instance()->push_waiting_group_files_for_user(index, (*it));
					}
				}
				delete content;
			}

			buffer[0] = '\0';

		}
		//erasing the socket from memory
		else
		{
		Close_socket:
			running = false;
			if (std::find(this->conected_device_sockets.begin(), this->conected_device_sockets.end(), clientSocket) != this->conected_device_sockets.end())
				conected_device_sockets.erase(std::remove(conected_device_sockets.begin(), conected_device_sockets.end(), clientSocket), conected_device_sockets.end());
			auto it = std::find(this->conected_users_sockets.begin(), this->conected_users_sockets.end(), clientSocket);
			if (it != this->conected_users_sockets.end())
				conected_users_sockets.erase(std::remove(conected_users_sockets.begin(), conected_users_sockets.end(), clientSocket), conected_users_sockets.end());
		}
	}
	std::cout << "Connection closed" << std::endl;
	closesocket(clientSocket);
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
			std::thread requestThread(&Connection_manager::requests, this, clientSock);
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
	for (auto friend_ = friend_list.begin(); friend_ != friend_list.end(); friend_++, friend_list_packet += ":")
	{
		friend_list_packet += *friend_;
	}
	if (!friend_list_packet.empty())
		friend_list_packet.pop_back();
	return friend_list_packet;
}

std::string Connection_manager::give_group_list(std::string username)
{
	std::string					group_list_packet;

	std::vector<std::string>	group_list;
	group_list = DB::get_instance()->get_group_list(username);
	for (auto member = group_list.begin(); member != group_list.end(); member++, group_list_packet += ":")
	{
		group_list_packet += *member;
	}
	if (!group_list_packet.empty())
		group_list_packet.pop_back();
	return group_list_packet;
}

void Connection_manager::register_(std::string email, std::string username, std::string password)
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

void Connection_manager::send_group_message_at_connection(SOCKET clientSocket, std::string receiver)
{
	std::vector<std::pair<std::string, std::string>> group_message;
	int												 messageLength;
	char											 message[2048] = "\0";
	group_message = DB::get_instance()->pop_waiting_group_messages(receiver);

	for (auto it = group_message.begin(); it != group_message.end(); it++)
	{
		strcpy(message, "Mesaj:");
		strcat(message, (*it).first.c_str());
		strcat(message, ":");
		strcat(message, receiver.c_str());
		strcat(message, ":");
		strcat(message, (*it).second.c_str());
		strcat(message, "\0");

		uint32_t dimension;
		dimension = strlen(message);
		messageLength = strlen(message);

		send(clientSocket, (char*)&dimension, sizeof(dimension), 0);
		send(clientSocket, message, messageLength, 0);
	}
	DB::get_instance()->delete_sent_group_messages(receiver);
}

void Connection_manager::send_message_for_connected_user(SOCKET receiver, std::string sender, std::string receiver_username, std::string message_content)
{
	char				message[2048];
	strcpy(message, "Mesaj:");
	strcat(message, sender.c_str());
	strcat(message, ":");
	strcat(message, receiver_username.c_str());
	strcat(message, ":");
	strcat(message, message_content.c_str());
	strcat(message, "\0");

	uint32_t messageLength = strlen(message);

	send(receiver, (char*)&messageLength, sizeof(messageLength), 0);
	send(receiver, message, messageLength, 0);
}

void Connection_manager::send_group_message_for_connected_user(SOCKET receiver, std::string group, std::string receiver_username, std::string message_content)
{
	char				message[2048];
	strcpy(message, "Mesaj:");
	strcat(message, group.c_str());
	strcat(message, ":");
	strcat(message, receiver_username.c_str());
	strcat(message, ":");
	strcat(message, message_content.c_str());
	strcat(message, "\0");

	uint32_t messageLength = strlen(message);

	send(receiver, (char*)&messageLength, sizeof(messageLength), 0);
	send(receiver, message, messageLength, 0);
}

void Connection_manager::send_files_at_connection(SOCKET clientSocket, std::string receiver)
{
	std::vector<std::pair<File, char*>>				 whole_file;
	char											 message[1024];
	int												 messageLength;
	whole_file = DB::get_instance()->pop_waiting_files(receiver);

	for (auto it = whole_file.begin(); it != whole_file.end(); it++)
	{
		message[0] = '\0';
		strcpy(message, "File:");
		strcat(message, (*it).first.get_sender().c_str());
		strcat(message, ":");
		strcat(message, (*it).first.get_receiver().c_str());
		strcat(message, ":");
		strcat(message, (*it).first.get_name().c_str());
		strcat(message, ":");
		strcat(message, std::to_string((*it).first.get_dimension()).c_str());
		strcat(message, "\0");

		uint32_t dimension;
		dimension = strlen(message);
		messageLength = strlen(message);

		send(clientSocket, (char*)&dimension, sizeof(dimension), 0);
		send(clientSocket, message, messageLength, 0);
		Sleep(10);
		//send(clientSocket, (*it).second, (*it).first.get_dimension(), 0);
		int						sent = 0;
		while (sent < (*it).first.get_dimension())
		{
			Sleep(10);
			int			bytesToSend = min(1024 * 3, (*it).first.get_dimension() - sent);
			send(clientSocket, (*it).second + sent, bytesToSend, 0);
			sent += 1024 * 3;

		}
	}

	DB::get_instance()->delete_sent_files(receiver);
}

void Connection_manager::send_group_files_at_connection(SOCKET clientSocket, std::string receiver)
{
	std::vector<std::pair<File, char*>>				 whole_file;
	char											 message[1024];
	int												 messageLength;
	whole_file = DB::get_instance()->pop_waiting_group_files(receiver);

	for (auto it = whole_file.begin(); it != whole_file.end(); it++)
	{
		message[0] = '\0';
		strcpy(message, "File:");
		strcat(message, (*it).first.get_receiver().c_str());
		strcat(message, ":");
		strcat(message, receiver.c_str());
		strcat(message, ":");
		strcat(message, (*it).first.get_name().c_str());
		strcat(message, ":");
		strcat(message, std::to_string((*it).first.get_dimension()).c_str());
		strcat(message, "\0");

		uint32_t dimension;
		dimension = strlen(message);
		messageLength = strlen(message);

		send(clientSocket, (char*)&dimension, sizeof(dimension), 0);
		send(clientSocket, message, messageLength, 0);
		Sleep(10);
		//send(clientSocket, (*it).second, (*it).first.get_dimension(), 0);
		int						sent = 0;
		while (sent < (*it).first.get_dimension())
		{
			Sleep(10);
			int			bytesToSend = min(1024 * 3, (*it).first.get_dimension() - sent);
			send(clientSocket, (*it).second + sent, bytesToSend, 0);
			sent += 1024 * 3;

		}

	}

	DB::get_instance()->delete_sent_group_files(receiver);
}

void Connection_manager::send_files_for_connected_client(SOCKET receiver, File& file, char* content)
{
	char				message[2048];
	strcpy(message, "File:");
	strcat(message, file.get_sender().c_str());
	strcat(message, ":");
	strcat(message, file.get_receiver().c_str());
	strcat(message, ":");
	strcat(message, file.get_name().c_str());
	strcat(message, ":");
	strcat(message, std::to_string(file.get_dimension()).c_str());
	strcat(message, "\0");

	uint32_t messageLength = strlen(message);

	send(receiver, (char*)&messageLength, sizeof(messageLength), 0);
	send(receiver, message, messageLength, 0);
	Sleep(10);

	int						sent = 0;
	while (sent < file.get_dimension())
	{
		Sleep(10);
		int			bytesToSend = min(1024 * 3, file.get_dimension() - sent);
		send(receiver, content + sent, bytesToSend, 0);
		sent += 1024 * 3;

	}

}

void Connection_manager::send_group_files_for_connected_client(SOCKET receiver, File& file, std::string receiver_username, char* content)
{
	char				message[2048];
	strcpy(message, "File:");
	strcat(message, file.get_receiver().c_str());
	strcat(message, ":");
	strcat(message, receiver_username.c_str());
	strcat(message, ":");
	strcat(message, file.get_name().c_str());
	strcat(message, ":");
	strcat(message, std::to_string(file.get_dimension()).c_str());
	strcat(message, "\0");

	uint32_t			messageLength = strlen(message);

	send(receiver, (char*)&messageLength, sizeof(messageLength), 0);
	send(receiver, message, messageLength, 0);
	Sleep(10);

	int						sent = 0;
	while (sent < file.get_dimension())
	{
		Sleep(10);
		int			bytesToSend = min(1024 * 3, file.get_dimension() - sent);
		send(receiver, content + sent, bytesToSend, 0);
		sent += 1024 * 3;

	}

}


