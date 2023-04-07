#pragma once
#include<iostream>
#include<string>
#include"_IException.h"
class Exception:public _IException
{
	std::string		message;
	int				code;
public:
					Exception(std::string message, int code);
	virtual			~Exception();
	virtual void	handle_exception();
};

