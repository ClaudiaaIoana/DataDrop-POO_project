#pragma once
#include"Exception.h"
class Exception_query:public Exception
{
public:
					Exception_query(std::string message, int code);
	virtual			~Exception_query();
};

