#pragma once
#include"Exception.h"
class Exception_alloc:public Exception
{
public:
					Exception_alloc(std::string message, int code);
	virtual			~Exception_alloc();
};

