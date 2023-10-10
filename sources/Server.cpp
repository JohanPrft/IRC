#include "../includes/irc.hpp"

void sendStringSocket(int socket, std::string str);

Server::Server(int port, string password, struct tm * timeinfo) :
		_port(port),
		_serverSocket(socket(AF_INET, SOCK_STREAM, 0)),
		_password(password)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
	std::string str(buffer);

	_datetime = str;
	if (_serverSocket == -1)
    {
		cerr_server("Error creating socket");
        return;
    }
	cout_server("created");
	cout_server("password is: " + _password);
	cout << GREEN << "[Server]: " << "running on port: " << _port << RESET << endl;
}

Server::~Server()
{
}


void Server::sendMessageToGroup(User *currentClient, std::vector<int> &clientsFds)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    bytesRead = recv(currentClient->getSocket(), buffer, sizeof(buffer), 0);
    if (bytesRead > 0)
    {
		User::cout_user(currentClient->getNickname() + " says: " + buffer);
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
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    bytesRead = recv(currentClient->getSocket(), buffer, sizeof(buffer), 0);
    if (bytesRead > 0)
    {
		User::cout_user(currentClient->getNickname() + " says: " + buffer);
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

void Server::handleNewConnection(std::vector<int> &clients)
{
    int clientSocket = accept(_serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        cerr_server("Error accepting client socket");
        return;
    }
    clients.push_back(clientSocket);

    pollfd clientFd;
    clientFd.fd = clientSocket;
    clientFd.events = POLLIN;
    _fds.push_back(clientFd);

    _users.insert(std::pair<int, User *>(clientSocket, new User(clientSocket, _password)));
    confirmClientConnection(_users[clientSocket]);
    map<int, User *>::iterator it = _users.find(clientSocket);
	cout_server("New connection from : " + it->second->getFullname());
}

void Server::handleClientDisconnect(std::vector<int> &clients, size_t index)
{
    put_str_fd("Server is disconnecting you now.\n", _fds[index].fd);
	cout_server(_users[_fds[index].fd]->getNickname() + " disconnected");
    close(_fds[index].fd);
    clients.erase(std::remove(clients.begin(), clients.end(), _fds[index].fd), clients.end());
    delete _users[_fds[index].fd];
    _users.erase(_fds[index].fd);
    _fds.erase(_fds.begin() + index);
}

void Server::handleExistingClient(std::vector<int> &clients, size_t index)
{
    User *currentClient = _users[_fds[index].fd];
    if (currentClient == NULL)
    {
		cerr_server("Error finding client");
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
		cerr_server("Error binding socket");
		return;
    }

    if (listen(_serverSocket, 5) == -1)
    {
		cerr_server("Error listening on socket");
        return;
    }

	cout_server("Listening...");
}

void Server::addServerSocketToEvents()
{
    pollfd serverFd;
    serverFd.fd = _serverSocket;
    serverFd.events = POLLIN;
    _fds.push_back(serverFd);
}

void Server::handleEvents(std::vector<int> &clients)
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
			cerr_server("Error polling");
            // return;
        }
    }
}

void Server::initServer()
{
    initializeServerSocket();
    addServerSocketToEvents();

    std::vector<int> clients;
    handleEvents(clients);
}

void    Server::confirmClientConnection(User *currentClient)
{
    std::string buffer;

    buffer = RPL_WELCOME(currentClient->getNickname(), currentClient->getUsername(), currentClient->getHostname());
    buffer += RPL_YOURHOST(currentClient->getNickname());
    buffer += RPL_CREATED(currentClient->getNickname(), _datetime);
    buffer += RPL_MYINFO(currentClient->getNickname());
    //buffer += RPL_MOTDSTART(currentClient->getNickname()); //optionnal
	sendStringSocket(currentClient->getSocket(), buffer);
}

void Server::cout_server(const string & msg) {
	cout << GREEN << "[Server]: " << msg << RESET << endl;
}

void Server::cerr_server(const string & msg) {
	cerr << RED << "[Server]: " << msg << RESET << endl;
}