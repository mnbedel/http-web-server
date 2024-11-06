#include "listener.h"
#include <iostream>
#include <string>
#include <sstream>

int Listener::initialize()
{
	WSADATA wsdata;
	WORD version = MAKEWORD(2, 2);

	int ok = WSAStartup(version, &wsdata);
	if (ok != 0)
	{
		return ok;
	}

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(_port);
	inet_pton(AF_INET, _ipaddress.c_str(), &hint.sin_addr);

	if (bind(_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	if (listen(_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	FD_ZERO(&_master);

	FD_SET(_socket, &_master);

	return 0;
}

int Listener::launch()
{
	bool running = true;

	while (running)
	{
		fd_set copy = _master;

		// Who's talking..
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == _socket)
			{
				SOCKET client = accept(_socket, nullptr, nullptr);

				FD_SET(client, &_master);

				whenClientConnected(static_cast<int>(client));
			}
			else // It's an inbound message
			{
				char buf[BUF_SIZE];
				ZeroMemory(buf, BUF_SIZE);

				int bytesIn = recv(sock, buf, BUF_SIZE, 0);
				if (bytesIn <= 0)
				{
					whenClientDisconnected(static_cast<int>(sock));
					closesocket(sock);
					FD_CLR(sock, &_master);
				}
				else
				{
					whenMessageReceived(static_cast<int>(sock), buf, bytesIn);
				}
			}
		}
	}

	FD_CLR(_socket, &_master);
	closesocket(_socket);

	while (_master.fd_count > 0)
	{
		SOCKET sock = _master.fd_array[0];

		FD_CLR(sock, &_master);
		closesocket(sock);
	}

	WSACleanup();
	return 0;
}


void Listener::sendToClient(int clientSocket, const char* msg, int length)
{
	send(clientSocket, msg, length, 0);
}

void Listener::broadcastToClients(int sendingClient, const char* msg, int length)
{
	for (size_t i = 0; i < _master.fd_count; i++)
	{
		SOCKET outSock = _master.fd_array[i];
		if (outSock != _socket && outSock != sendingClient)
		{
			sendToClient(static_cast<int>(outSock), msg, length);
		}
	}
}

void Listener::whenClientConnected(int clientSocket)
{

}

void Listener::whenClientDisconnected(int clientSocket)
{

}

void Listener::whenMessageReceived(int clientSocket, const char* msg, int length)
{

}