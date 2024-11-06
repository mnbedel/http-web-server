#pragma once

#include "listener.h"

class Server : public Listener
{
public:

	Server(std::string ipAddress, int port) :
		Listener(ipAddress, port) { }

protected:

	virtual void whenClientConnected(int clientSocket);

	virtual void whenClientDisconnected(int clientSocket);

	virtual void whenMessageReceived(int clientSocket, const char* msg, int length);
};
