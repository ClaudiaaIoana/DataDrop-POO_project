#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#include"Connection_manager.h"

int main()
{
	Connection_manager* con = Connection_manager::get_instance();
	con->listen_();
}