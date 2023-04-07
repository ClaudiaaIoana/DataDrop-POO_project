#pragma once
#include"Exception.h"
class Exception_connecting_db:public Exception
{
public:
	Exception_connecting_db(std::string message, int code);
	virtual			~Exception_connecting_db();
	virtual void	handle_exception();
};

