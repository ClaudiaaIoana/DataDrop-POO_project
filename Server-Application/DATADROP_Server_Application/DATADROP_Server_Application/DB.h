#pragma once
#include"_IDB.h"
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<vector>

#define SQL_RESULT_LEN		240
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
	static DB*						get_instance();
	static void						destroy_instance();
	void							resetHanddle();
	bool							verify_account(std::string username, std::string password);
	void							add_account(std::string username, std::string email, std::string password);
	bool							add_friend(std::string user1, std::string user2);
	std::vector<std::string>		get_friend_list(std::string username);
	void							push_waiting_message(std::string sender, std::string receiver, std::string message);
};

