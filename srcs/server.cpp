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


	// permet de retutiliser rapidement une socket meme si elle a ete kill
	const int	enable = 1;
	setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

	if (bind(_serverSocket, reinterpret_cast<sockaddr*>(&_serverAddress), sizeof(_serverAddress)) == -1)
	{
		std::cerr << "Error binding socket" << std::endl;
		return; // gere ici exeception
	}

	if (listen(_serverSocket, 5) == -1) //backlog max in queue
	{
		std::cerr << "Error listening on socket" << std::endl;
		return; // gere ici exeception
	}
	if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error putting socket on non bloking mode" << std::endl;
		return; // gere ici exeception
	}
	std::cout << "Listening..." << std::endl;


}