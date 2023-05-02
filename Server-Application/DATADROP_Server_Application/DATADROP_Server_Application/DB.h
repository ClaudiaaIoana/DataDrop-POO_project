#pragma once
#include"_IDB.h"
#include"File.h"
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<vector>

#define SQL_RESULT_LEN		3000
#define SQL_RETURN_CODE_LEN 1000

class DB:public _IDB
{
private:
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt;
	static DB*		instance;
	DB();
	~DB();
public:
	static DB*												get_instance();
	static void												destroy_instance();
	void													resetHanddle();
	bool													verify_account(std::string username, std::string password);
	void													add_account(std::string username, std::string email, std::string password);
	bool													add_friend(std::string user1, std::string user2);
	std::vector<std::string>								get_friend_list(std::string username);
	void													push_waiting_message(std::string sender, std::string receiver, std::string message);
	std::vector<std::pair<std::string, std::string>> 		pop_waiting_messages(std::string user);
	void													delete_sent_messages(std::string receiver);
	void													create_group_with_members(std:: string group_name, std::vector<std::string> users);
	void													create_empty_group(std::string group_name);
	void													add_member_in_group(std::string group_name,std::string username);
	void													push_waiting_files(File& file);
};

