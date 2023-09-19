#include "../includes/server.hpp"

Server::Server(int port, string password) : 
	_port(port),
	_serverSocket(socket(AF_INET, SOCK_STREAM, 0)),
	_password(password)
	{}


Server::~Server()
{}

void	Server::initServer()
{
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_port = htons(_port);
	_serverAddress.sin_addr.s_addr = INADDR_ANY;


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

	int clientSocket = accept(_serverSocket, NULL, NULL); //addr and addr_len unknown
	cout << clientSocket << endl;
	if (clientSocket == -1)
	{
		std::cerr << "Error accepting client socket" << std::endl;
		return ;
	}
	std::cout << "Client connected" << std::endl;

	char buffer[1024];
	ssize_t bytesRead;
	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
	{
		std::cout << "Received " << bytesRead << " bytes from client :" << std::endl;
		std::cout.write(buffer, bytesRead);
		bzero(buffer, sizeof(buffer));
	}

	if (bytesRead == -1)
		std::cerr << "Error receiving data from client" << std::endl;

	close(clientSocket);
	close(_serverSocket);

}