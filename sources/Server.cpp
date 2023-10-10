#include "../includes/irc.hpp"

void sendStringSocket(int socket, string str);

Server::Server(int port, string password, struct tm * timeinfo) :
		_port(port),
		_serverSocket(socket(AF_INET, SOCK_STREAM, 0)),
		_password(password)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
	string str(buffer);

	_datetime = str;
	if (_serverSocket == -1)
    {
        cerr << "Error creating socket" << endl;
        return;
    }
    cout << "Server password is :" << _password << endl;
    cout << "Server running on port :" << _port << endl;
}

Server::~Server()
{
}


void Server::sendMessageToGroup(User *currentClient, vector<int> &clientsFds)
{
    char buffer[1024];
    ssize_t bytesRead;

    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    bytesRead = recv(currentClient->getSocket(), buffer, sizeof(buffer), 0);
    if (bytesRead > 0)
    {
        cout << currentClient->getNickname() << " says: ";
        cout.write(buffer, bytesRead);
        for (size_t i = 0; i < clientsFds.size(); i++)
        {
            if (clientsFds[i] != currentClient->getSocket()) // don't send the message back to the client that sent it
            {
                put_str_fd(currentClient->getNickname(), clientsFds[i]);
                put_str_fd(" says: ", clientsFds[i]);
                write(clientsFds[i], buffer, bytesRead);
            }
        }
    }
    else
    {
        throw std::runtime_error("Error reading from client socket");
    }
    return ;
}

void Server::sendMessageToUser(User *currentClient, User *targetClient)
{
    char buffer[1024];
    ssize_t bytesRead;

    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    bytesRead = recv(currentClient->getSocket(), buffer, sizeof(buffer), 0);
    if (bytesRead > 0)
    {
        cout << currentClient->getNickname() << " says: ";
        cout.write(buffer, bytesRead);
        put_str_fd(currentClient->getNickname(), targetClient->getSocket());
        put_str_fd(" says: ", targetClient->getSocket());
        write(targetClient->getSocket(), buffer, bytesRead);
    }
    else
    {
        throw std::runtime_error("Error reading from client socket");
    }
    return ;
}

void Server::handleNewConnection(vector<int> &clients)
{
    int clientSocket = accept(_serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        cerr << "Error accepting client socket" << endl;
        return;
    }
    clients.push_back(clientSocket);

    pollfd clientFd;
    clientFd.fd = clientSocket;
    clientFd.events = POLLIN;
    _fds.push_back(clientFd);
	cout << "test" << endl;

    _users.insert(std::pair<int, User *>(clientSocket, new User(clientSocket, _password)));
    confirmClientConnection(_users[clientSocket]);
    map<int, User *>::iterator it = _users.find(clientSocket);
    cout << "New connection from : " << it->second->getFullname() << endl;
}

void Server::handleClientDisconnect(vector<int> &clients, size_t index)
{
    put_str_fd("Server is disconnecting you now.\n", _fds[index].fd);
    cout << _users[_fds[index].fd]->getNickname() << " disconnected" << endl;
    close(_fds[index].fd);
    clients.erase(remove(clients.begin(), clients.end(), _fds[index].fd), clients.end());
    delete _users[_fds[index].fd];
    _users.erase(_fds[index].fd);
    _fds.erase(_fds.begin() + index);
}

void Server::handleExistingClient(vector<int> &clients, size_t index)
{
    User *currentClient = _users[_fds[index].fd];
    if (currentClient == NULL)
    {
        cerr << "Error finding client" << endl;
        return;
    }
    try
    {
        sendMessageToGroup(currentClient, clients);
    }
    catch (const std::runtime_error &e)
    {
        handleClientDisconnect(clients, index);
    }
}

void Server::initializeServerSocket()
{
    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_port = htons(_port);
    _serverAddress.sin_addr.s_addr = INADDR_ANY;

    const int enable = 1;
    setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    if (bind(_serverSocket, reinterpret_cast<sockaddr *>(&_serverAddress), sizeof(_serverAddress)) == -1)
    {
        cerr << "Error binding socket" << endl;
        return;
    }

    if (listen(_serverSocket, 5) == -1)
    {
        cerr << "Error listening on socket" << endl;
        return;
    }

    cout << "Listening..." << endl;
}

void Server::addServerSocketToEvents()
{
    pollfd serverFd;
    serverFd.fd = _serverSocket;
    serverFd.events = POLLIN;
    _fds.push_back(serverFd);
}

void Server::handleEvents(vector<int> &clients)
{
    while (true)
    {
        int activity = poll(&_fds[0], _fds.size(), -1);
        if (activity >= 0)
        {
            for (size_t i = 0; i < _fds.size(); ++i)
            {
                if (_fds[i].revents & POLLIN)
                {
                    if (_fds[i].fd == _serverSocket)
                    {
                        handleNewConnection(clients);
                    }
                    else
                    {
                        handleExistingClient(clients, i);
                    }
                }
                else if (_fds[i].revents & POLLHUP)
                {
                    handleClientDisconnect(clients, i);
                }
            }
        }
        else if (activity == -1)
        {
            cerr << "Error polling" << endl;
            // return;
        }
    }
}

void Server::initServer()
{
    initializeServerSocket();
    addServerSocketToEvents();

    vector<int> clients;
    handleEvents(clients);
}

void    Server::confirmClientConnection(User *currentClient)
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

	//accept a call

	// Create a pollfd struct for the server socket
	pollfd serverFd;
	serverFd.fd = _serverSocket;
	serverFd.events = POLLIN;
	// Add the server socket to the pollfd vector
	_fds.push_back(serverFd);

	std::vector<int> clients;
	while (true)
	{
		

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
		std::cout << "Activity : " << activity << std::endl;
    	if (activity > 0)
		{
        	for (size_t i = 0; i < _fds.size(); ++i)
			{
            	if (_fds[i].revents & POLLIN)
				{
					std::cout << "Activity : " << activity << " of " << _fds[i].fd << std::endl;
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

						std::string buffer = User::receiveInfo(clientSocket);
						_users.insert(std::pair<int, User*>(clientSocket, new User(clientSocket, buffer)));
					}
					else
					{
						// Existing client has incoming data
						if(handleClient(_fds[i].fd, clients) == -1)
						{
							std::cout << "Client " << _fds[i].fd << " disconnected" << std::endl;
							clients.erase(std::remove(clients.begin(), clients.end(), _fds[i].fd), clients.end());
							//delete _users[_fds[i].fd];
							//_users.erase(_fds[i].fd);
							close(_fds[i].fd);
						}
                    
                	}
            	}
				else if (_fds[i].revents & POLLHUP)
				{
					// Client disconnected
					std::cout << "Client " << _fds[i].fd << " disconnected" << std::endl;
					clients.erase(std::remove(clients.begin(), clients.end(), _fds[i].fd), clients.end());
					delete _users[_fds[i].fd];
					_users.erase(_fds[i].fd);
					close(_fds[i].fd);

				}
			}
		}
		else if (activity == -1)
		{
        	std::cerr << "Error polling" << std::endl;
			//return;
    	}
	}

	for (size_t i = 0; i < clients.size(); ++i)
	{
		close(clients[i]);
	}
	close(_serverSocket);
}

