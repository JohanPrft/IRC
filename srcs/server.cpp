#include "../includes/server.hpp"

Server::Server(int port, string password) : _port(port) , _password(password)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}