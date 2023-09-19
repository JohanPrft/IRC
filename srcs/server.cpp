#include "../includes/server.hpp"

Server::Server(int port, string password) : 
	_port(port),
	_password(password),
	_serverSocket(socket(AF_INET, SOCK_STREAM, 0))
	{}


Server::~Server()
{}

void	Server::initServer()
{
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
}