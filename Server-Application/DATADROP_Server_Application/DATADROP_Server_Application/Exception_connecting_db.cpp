#include "Exception_connecting_db.h"
#include"Exception.h"
#include"DB.h"

Exception_connecting_db::Exception_connecting_db(std::string message, int code)
	:Exception(message,code)
{
}

Exception_connecting_db::~Exception_connecting_db()
{
}

void Exception_connecting_db::handle_exception()
{
	std::cout << "EXCEPTION TRIGGERED: " << message << " (code: " << code << ")" << std::endl;
	DB::destroy_instance();
}
