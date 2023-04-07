#pragma once
#include"Exception.h"
class Exception_sending:public Exception
{
public:
	Exception_sending(std::string message, int code);
	virtual			~Exception_sending();
	virtual void	handle_exception();
};

