#include "../includes/Server.hpp"

Server::Server(int port, string password) : 
	_port(port),
	_serverSocket(socket(AF_INET, SOCK_STREAM, 0)),
	_password(password)
{
	cout << "Server password is :" << _password << endl;
	cout << "Server running on port :" << _port << endl;
}


Server::~Server()
{}

int handleClient(int clientSocket, std::vector<int>& clients)
{
	char buffer[1024];
  	ssize_t bytesRead;

	bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytesRead > 0)
	{
		std::cout << clientSocket << " says: ";
    	std::cout.write(buffer, bytesRead);
		for (size_t i = 0; i < clients.size(); ++i)
		{
			if (clients[i] != clientSocket) // don't send the message back to the client that sent it
			{  
				write(clients[i], "Client ", 7);

				char clientSocketStr[10];
				std::sprintf(clientSocketStr, "%d", clientSocket);

				write(clients[i], clientSocketStr, strlen(clientSocketStr));
				write(clients[i], " says: ", 7);
				write(clients[i], buffer, bytesRead);
			}
		}
	}
	if (bytesRead == -1)
	{
		std::cerr << "Error receiving data from client" << std::endl;
		return -1;
	}
	if (bytesRead == 0)
	{
		std::cout << "Client " << clientSocket << " disconnected" << std::endl;
		return -1;
	}
    bzero(buffer, sizeof(buffer));
	return 0;
}

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
	// if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1)
	// {
	// 	std::cerr << "Error putting socket on non bloking mode" << std::endl;
	// 	return; // gere ici exeception
	// }
	std::cout << "Listening..." << std::endl;

	//accept a call

	// Create a pollfd struct for the server socket
	pollfd serverFd;
	serverFd.fd = _serverSocket;
	serverFd.events = POLLIN;
	_fds.push_back(serverFd);

	std::vector<int> clients;
	while (true)
	{
		// Add the server socket to the pollfd vector
		// _fds.clear();

    	// Add the client sockets to the pollfd vector
    	for (size_t i = 0; i < clients.size(); ++i)
		{
        	pollfd clientFd;
        	clientFd.fd = clients[i];
        	clientFd.events = POLLIN;
        	_fds.push_back(clientFd);
    	}

    	// Use poll to wait for activity on any of the file descriptors
    	int activity = poll(&_fds[0], _fds.size(), -1);
    	if (activity > 0)
		{
        	for (size_t i = 0; i < _fds.size(); ++i)
			{
            	if (_fds[i].revents & POLLIN)
				{
                	if (_fds[i].fd == _serverSocket)
					{
                    	// New client connection
                    	int clientSocket = accept(_serverSocket, NULL, NULL);
                    	if (clientSocket == -1)
						{
                        	std::cerr << "Error accepting client socket" << std::endl;
                        	return;
                    	}
                    	std::cout << "Client " << clientSocket << " connected" << std::endl;
                    	clients.push_back(clientSocket);
                	} 
					else
					{
						// Existing client has incoming data
						if(handleClient(_fds[i].fd, clients) == -1)
						{
							clients.erase(std::remove(clients.begin(), clients.end(), _fds[i].fd), clients.end());
							close(_fds[i].fd);
						}
                    
                	}
            	}
        	}
    	}
		else if (activity == -1)
		{
        	std::cerr << "Error polling" << std::endl;
			return;
    	}

	}
	for (size_t i = 0; i < clients.size(); ++i)
	{
		close(clients[i]);
	}
	close(_serverSocket);
}