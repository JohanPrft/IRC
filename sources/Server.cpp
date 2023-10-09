#include "../includes/Server.hpp"
#include "../includes/User.hpp"

Server::Server(int port, string password) : _port(port),
											_serverSocket(socket(AF_INET, SOCK_STREAM, 0)),
											_password(password)
{
	if (_serverSocket == -1)
	{
		std::cerr << "Error creating socket" << std::endl;
		return;
	}
	cout << "Server password is :" << _password << endl;
	cout << "Server running on port :" << _port << endl;
}

Server::~Server()
{
}

void print_pollfd(vector<pollfd> _fds)
{
	for (size_t i = 0; i < _fds.size(); ++i)
	{
		std::cout << _fds[i].fd << " ";
	}
	std::cout << std::endl;
}

int handleClient(User *currentClient, std::vector<int> &clients)
{
	char buffer[1024];
	ssize_t bytesRead;

	memset(buffer, 0, sizeof(buffer)); // clear the buffer
	bytesRead = recv(currentClient->getSocket(), buffer, sizeof(buffer), 0);
	if (bytesRead > 0)
	{
		std::cout << currentClient->getNickname() << " says: ";
		std::cout.write(buffer, bytesRead);
		for (size_t i = 0; i < clients.size(); i++)
		{
			if (clients[i] != currentClient->getSocket()) // don't send the message back to the client that sent it
			{
				put_str_fd(currentClient->getNickname(), clients[i]);
				put_str_fd(" says: ", clients[i]);
				write(clients[i], buffer, bytesRead);
			}
		}
	}
	else
	{
		return -1;
	}
	return 0;
}

void Server::initServer()
{
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_port = htons(_port);
	_serverAddress.sin_addr.s_addr = INADDR_ANY;

	// permet de retutiliser rapidement une socket meme si elle a ete kill
	const int enable = 1;
	setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

	if (bind(_serverSocket, reinterpret_cast<sockaddr *>(&_serverAddress), sizeof(_serverAddress)) == -1)
	{
		std::cerr << "Error binding socket" << std::endl;
		return; // gere ici exeception
	}

	if (listen(_serverSocket, 5) == -1) // backlog max in queue
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

	// accept a call

	// Create a pollfd struct for the server socket
	pollfd serverFd;
	serverFd.fd = _serverSocket;
	serverFd.events = POLLIN;
	// Add the server socket to the pollfd vector
	_fds.push_back(serverFd);

	std::vector<int> clients;
	while (true)
	{
		// Use poll to wait for activity on any of the file descriptors
		int activity = poll(&_fds[0], _fds.size(), -1);
		if (activity >= 0)
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
						clients.push_back(clientSocket);

						// Add the client sockets to the pollfd vector
						pollfd clientFd;
						clientFd.fd = clientSocket;
						clientFd.events = POLLIN;
						_fds.push_back(clientFd);

						_users.insert(std::pair<int, User *>(clientSocket, new User(clientSocket)));
						map<int, User *>::iterator it = _users.find(clientSocket);
						std::cout << "New connection from : " << it->second->getFullname() << std::endl;
					}
					else
					{
						// Existing client has incoming data
						
						User *currentClient = _users[_fds[i].fd];
						if (currentClient == NULL)
						{
							std::cerr << "Error finding client" << std::endl;
							return;
						}
						if (handleClient(currentClient, clients) == -1)
						{
							put_str_fd("Server is disconnecting you now.\n", _fds[i].fd);
							std::cout << currentClient->getNickname() << " disconnected" << std::endl;

							close(_fds[i].fd);
							clients.erase(std::remove(clients.begin(), clients.end(), _fds[i].fd), clients.end());
							delete currentClient;
							_users.erase(_fds[i].fd);
							_fds.erase(_fds.begin() + i);
						}
					}
				}
				else if (_fds[i].revents & POLLHUP)
				{
					put_str_fd("Server is disconnecting you now.\n", _fds[i].fd);
					std::cout << _users[_fds[i].fd]->getNickname() << " disconnected" << std::endl;
					close(_fds[i].fd);
					clients.erase(std::remove(clients.begin(), clients.end(), _fds[i].fd), clients.end());
					delete _users[_fds[i].fd];
					_users.erase(_fds[i].fd);
					_fds.erase(_fds.begin() + i);
				}
			}
		}
		else if (activity == -1)
		{
			std::cerr << "Error polling" << std::endl;
			// return;
		}
	}

	for (size_t i = 0; i < clients.size(); ++i)
	{
		close(clients[i]);
	}
	close(_serverSocket);
}
