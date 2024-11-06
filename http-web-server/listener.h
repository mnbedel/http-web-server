#pragma once

#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

#define BUF_SIZE 4096

class Listener
{
	std::string		_ipaddress;
	int				_port;
	SOCKET			_socket;
	fd_set			_master;

public:

	Listener(std::string ipAddress, int port) :
		_ipaddress(ipAddress), _port(port) { }

	int initialize();

	int launch();

protected:

	virtual void whenClientConnected(int clientSocket);

	virtual void whenClientDisconnected(int clientSocket);

	virtual void whenMessageReceived(int clientSocket, const char* msg, int length);

	void sendToClient(int clientSocket, const char* msg, int length);

	void broadcastToClients(int sendingClient, const char* msg, int length);
};