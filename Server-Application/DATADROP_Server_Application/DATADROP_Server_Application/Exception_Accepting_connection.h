#pragma once
#include"Exception.h"
class Exception_Accepting_connection:public Exception
{
public:
	Exception_Accepting_connection(std::string message, int code);
	virtual			~Exception_Accepting_connection();
	virtual void	handle_exception();
};

