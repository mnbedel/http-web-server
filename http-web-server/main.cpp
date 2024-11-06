#include "Server.h"

int main()
{
	Server server(std::string{ "127.0.0.1" }, 8080);
	if (server.initialize() != 0)
		return -1;

	server.launch();
	system("pause");

	return 0;
}