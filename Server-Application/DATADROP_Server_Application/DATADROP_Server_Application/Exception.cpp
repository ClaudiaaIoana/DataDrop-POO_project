#include "Exception.h"

Exception::Exception(std::string message, int code)
	:message(message),code(code)
{
}

Exception::~Exception()
{
}

void Exception::handle_exception()
{
	std::cout << "EXCEPTION TRIGGERED: " << message << " (code: " << code << ")" << std::endl;
}
