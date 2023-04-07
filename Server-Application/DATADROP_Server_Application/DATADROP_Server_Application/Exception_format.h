#pragma once
#include"Exception.h"
class Exception_format:public Exception
{
public:
	Exception_format(std::string message, int code);
	virtual			~Exception_format();
	virtual void	handle_exception();
};

