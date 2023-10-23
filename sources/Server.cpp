#include "../includes/irc.hpp"
#include "command.hpp"

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

vector<string> Server::parseCommand(string& command)
{
		vector<string> splitedCommand;
		replaceAll(command, "\r", "");
		replaceAll(command, "\n", " ");
		for (size_t i = 0; i < command.length(); ++i) //force space after <+/-><letter>
		{
			if ((command[i] == '+' || command[i] == '-') && i + 1 < command.length() && command[i + 1] != ' '
				&& i + 2 < command.length() && command[i + 2] != ' ')
			{
				command.insert(i + 2, " ");
				i += 2;
			}
		}
		split(command, ' ' , splitedCommand);
		return (splitedCommand);
}

void Server::execCommand(User *user, vector<string> splitedCommand)
{
	if (splitedCommand.size() < 2)
		return;

	string command = splitedCommand[0];
	if (command == "PING")
		ping(user->getSocket(), user, splitedCommand);
	else if (command == "NICK")
		nick(this, user, splitedCommand);
	else if (command == "USER")
		username(user, splitedCommand);
	else if (command == "MODE")
		mode(this, user, splitedCommand);
	else if (command =="PRIVMSG")
        privmsg(user, splitedCommand);
	else if (command == "JOIN")
		join(user, splitedCommand);
    else if (command == "KICK")
        kick(user, splitedCommand);
	else if (command == "INVITE")
		invite(user, splitedCommand);
}

void	Server::receiveCommand(User *currentClient)
{
	char buffer[1024];
    ssize_t bytesRead;

    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    bytesRead = recv(currentClient->getSocket(), buffer, sizeof(buffer), 0);
	if (bytesRead > 0)
    {
		string str(buffer);
		currentClient->cout_user(str);
		vector<string> splitedCommand = parseCommand(str);
		currentClient->cout_user(str);
		execCommand(currentClient, splitedCommand);
	}		
    return ;
}

void Server::handleNewConnection(vector<int> &clients)
{
    int clientSocket = accept(_serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        cerr_server("Error accepting client socket");
        return;
    }

	User *user = new User(this, clientSocket, _password);
	if (!user->getIsLogged())
	{
		delete user;
		return;
	}

    clients.push_back(clientSocket);
    pollfd clientFd;
    clientFd.fd = clientSocket;
    clientFd.events = POLLIN;
    _fds.push_back(clientFd);

    _users.insert(std::pair<int, User *>(clientSocket, user));
    confirmClientConnection(_users[clientSocket]);
    map<int, User *>::iterator it = _users.find(clientSocket);
	cout_server("New connection from : " + it->second->getFullname());
}

void Server::handleClientDisconnect(vector<int> &clients, size_t index)
{
    put_str_fd("Server is disconnecting you now.\n", _fds[index].fd);
	cout_server(_users[_fds[index].fd]->getNickname() + " disconnected");
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
		cerr_server("Error finding client");
        return;
    }
    try
    {
        receiveCommand(currentClient);
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

	cout_server("listening...");
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
			cerr_server("Error polling");
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
    string buffer;

    buffer = RPL_WELCOME(user_id(currentClient->getNickname(), currentClient->getUsername()), currentClient->getNickname());
    buffer += RPL_YOURHOST(currentClient->getNickname(), SERVERNAME, VERSION);
    buffer += RPL_CREATED(currentClient->getNickname(), _datetime);
    buffer += RPL_MYINFO(currentClient->getNickname(), SERVERNAME, VERSION, USERMODE, CHANMODE, CHANMODE);
	buffer += RPL_ISUPPORT(currentClient->getNickname(), "CHANNELLEN=32 NICKLEN=9 TOPICLEN=307");
	sendStringSocket(currentClient->getSocket(), buffer);
}

void	Server::sendMessageToChannel(Channel *currentChannel, User *currentClient, string msg)
{
    vector<User *>listClient = currentChannel->getUserList();
    for (size_t i = 0; i < listClient.size() ; i++)
    {
        if (listClient[i]->getSocket() != currentClient->getSocket())
        {
            sendStringSocket(listClient[i]->getSocket(), RPL_PRIVMSG(currentClient->getNickname(), currentClient->getUsername(), currentChannel->getName(), msg));
        }
    }
	return ;
}

void Server::sendMessageToUser(User *currentClient, User *targetClient, string msg)
{
    sendStringSocket(targetClient->getSocket(), RPL_PRIVMSG(currentClient->getNickname(), currentClient->getUsername(), targetClient->getNickname(), msg));
    return ;
}

void Server::cout_server(const string & msg) {
	cout << GREEN << "[Server]: " << msg << RESET << endl;
}

void Server::cerr_server(const string & msg) {
	cerr << RED << "[Server]: " << msg << RESET << endl;
}

Channel *Server::getChannel(const string& name) {
    map<string, Channel*>::iterator iter = _channels.find(name);
    if (iter == _channels.end())
        return NULL;
    return iter->second;
}

bool Server::channelExist(string channelName)
{
	map<string, Channel*>::iterator it = _channels.find(channelName);

    if (it != _channels.end())
        return true;
     else 
        return false;
}

int Server::getFdUser(User *user)
{
	std::map<int, User*>::iterator it;
	for (it = _users.begin(); it != _users.end(); ++it) 
        if (it->second == user) 
			return it->first;
    return -1;
}

User* Server::userExist(string username)
{
	std::map<int, User*>::iterator it;
	for (it = _users.begin(); it != _users.end(); ++it) 
        if (it->second->getNickname() == username) 
			return it->second;
	return NULL;
}

