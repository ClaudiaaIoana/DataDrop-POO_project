#pragma once
#include"_IDB.h"
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

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
	static DB*		get_instance();
	static void		destroy_instance();
	bool verify_account(std::string username, std::string password);
	void add_account(std::string username, std::string email, std::string password);
};

