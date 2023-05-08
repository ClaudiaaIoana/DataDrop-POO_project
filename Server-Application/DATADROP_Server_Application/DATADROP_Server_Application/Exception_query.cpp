#include "Exception_query.h"

Exception_query::Exception_query(std::string message, int code)
	:Exception(message,code)
{
}

Exception_query::~Exception_query()
{
}
