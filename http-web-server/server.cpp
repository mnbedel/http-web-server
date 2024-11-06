#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <iterator>
#include "Server.h"

void Server::whenMessageReceived(int clientSocket, const char* msg, int length)
{
	std::istringstream iss(msg);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	// Defaults for output
	std::string content = "<h1>404 Not Found</h1>";
	std::string htmlFile = "/index.html";
	int errorCode = 404;

	if (parsed.size() >= 3 && parsed[0] == "GET")
	{
		htmlFile = parsed[1];

		// If the file is just a slash, use index.html.
		if (htmlFile == "/")
		{
			htmlFile = "/index.html";
		}
	}

	std::ifstream file(".\\wwwroot" + htmlFile);

	if (file.good())
	{
		std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		content = str;
		errorCode = 200;
	}

	file.close();

	// Write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << errorCode << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	size_t size = output.size() + 1;

	sendToClient(clientSocket, output.c_str(), static_cast<int>(size));
}

void Server::whenClientConnected(int clientSocket)
{
	std::cout << "client connected.." << std::endl;
}

void Server::whenClientDisconnected(int clientSocket)
{
	std::cout << "client disconnected.." << std::endl;
}