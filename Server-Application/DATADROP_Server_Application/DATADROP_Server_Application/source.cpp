#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#include"Connection_manager.h"
#include"DB.h"

int main()
{
	DB* db = DB::get_instance();
	Connection_manager* con = Connection_manager::get_instance();
	con->listen_();

	db->destroy_instance();

	return 0;
}