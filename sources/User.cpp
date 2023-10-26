#include "../includes/irc.hpp"
#include "User.hpp"


// Intercept and process the first 3 messages

User::User()
{
    _nickname = "Undefined";
    _username = "Undefined";
    _fullname = "Undefined";
    _hostname = "Undefined";
    _clientSocket = -1;
    _isLogged = false;
    _buffer = "";
}


void put_str_fd(const string& str, int fd)
{
    write(fd, str.c_str(), str.length());
}

bool User::isNickValidOnConnect(Server *serv, User *user)
{
	if (serv->userExist(user->_nickname))
	{
		sendStringSocket(user->getSocket(), ERR_NICKNAMEINUSE(user->_nickname, user->_nickname));
		Server::cout_server(ERR_NICKNAMEINUSE(user->_nickname, user->_nickname));
		sendStringSocket(_clientSocket, "You aren't logged in, please reconnect with a valid nickname (already in use)\n");
		return (false);
	}
	else if (user->_nickname.find_first_not_of(AUTHORISED_CHAR_NICK) != string::npos)
	{
		sendStringSocket(user->getSocket(), ERR_ERRONEUSNICKNAME(user->_nickname, user->_nickname));
		Server::cout_server(ERR_ERRONEUSNICKNAME(user->_nickname, user->_nickname));
		sendStringSocket(_clientSocket, "You aren't logged in, please reconnect with a valid nickname (forbidden char)\n");
		return (false);
	}
	else
		return (true);
}

bool User::isNickValid(Server *serv, User *user, const string &nick, int clientSocket)
{
	if (serv->userExist(nick))
	{
		sendStringSocket(clientSocket, ERR_NICKNAMEINUSE(user->getNickname(), nick));
		Server::cout_server(ERR_NICKNAMEINUSE(user->getNickname(), nick));
		sendStringSocket(clientSocket, RPL_NICK(user->getNickname(), user->getUsername(), user->getNickname()));
		Server::cout_server(RPL_NICK(user->getNickname(), user->getUsername(), user->getNickname()));
		return (false);
	}
	else if (nick.find_first_not_of(AUTHORISED_CHAR_NICK) != string::npos)
	{
		sendStringSocket(clientSocket, ERR_ERRONEUSNICKNAME(user->getNickname(), nick));
		Server::cout_server(ERR_ERRONEUSNICKNAME(user->getNickname(), nick));
		sendStringSocket(clientSocket, RPL_NICK(user->getNickname(), user->getUsername(), user->getNickname()));
		Server::cout_server(RPL_NICK(user->getNickname(), user->getUsername(), user->getNickname()));
		return (false);
	}
	else
		return (true);
}

//register client
User::User(Server *serv, int clientSocket, const string &password)
{
    _clientSocket = clientSocket;
    put_str_fd("Welcome to the IRC server!\n", _clientSocket);

	string userInfo = getUserInfo(_clientSocket);
	cout_user(userInfo);
	try {
		fillUserInfo(userInfo, password);
	}
	catch (const std::exception& e) {
		Server::cerr_server(e.what());
	}
    if (!_isLogged || !isNickValidOnConnect(serv, this))
	{
		_isLogged = false;
		put_str_fd("You aren't logged in, given infos aren't valid\nPlease reconnect\n", _clientSocket);
        close(_clientSocket);
    }
}

User::User(const User &src) {
    _clientSocket = src._clientSocket;
    _nickname = src._nickname;
    _username = src._username;
    _fullname = src._fullname;
    _hostname = src._hostname;
    _isLogged = src._isLogged;
}

User &User::operator=(const User &cpy) {
	if (this != &cpy) {
        _clientSocket = cpy._clientSocket;
        _nickname = cpy._nickname;
        _username = cpy._username;
        _fullname = cpy._fullname;
        _hostname = cpy._hostname;
        _isLogged = cpy._isLogged;
	}
	return (*this);
}

User::~User()
{
	return ;
}

ostream& operator<<(ostream& os, const User& user) {
    os << "Nickname: " << user.getNickname() << endl;
    os << "Username: " << user.getUsername() << endl;
    os << "Fullname: " << user.getFullname() << endl;
    os << "Hostname: " << user.getHostname() << endl;
    os << "Socket: " << user.getSocket() << endl;
    os << "Logged: " << user.getIsLogged() << endl;
    return os;
}

string User::getNickname() const {
    return (_nickname);
}

string User::getUsername() const {
    return (_username);
}

string User::getFullname() const {
    return (_fullname);
}

string User::getHostname() const {
    return (_hostname);
}

int User::getIsLogged() const {
    return (_isLogged);
}

int User::getSocket() const {
    return (_clientSocket);
}

void	User::setLogged(bool logged) {
    _isLogged = logged;
}

void User::setNickname(const string &nick) {
	_nickname = (_nickname.size() > 9) ? nick.substr(0, 9) : nick;
}

void User::setUsername(const string &username) {
	_username = username;
}

static bool checkUserInfo(const string& userInfo)
{
	if (userInfo.find("NICK") == string::npos)
		return (false);
	else if (userInfo.find("USER") == string::npos)
		return (false);
	else if (userInfo.find("PASS") == string::npos)
		return (false);
	return (true);
}

string User::getUserInfo(int clientSocket) const {
	string userInfo;
	char buffer[BUFFER_SIZE];
	while (!checkUserInfo(userInfo))
	{
		ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesRead == -1 || bytesRead == 0) {
			cerr << "Error reading from client." << endl;
			break;
		} else if (bytesRead == 0) {
			// Client disconnected prematurely
			break;
		}
		// Process the message
		userInfo += string(buffer, bytesRead);
		bzero(buffer, sizeof(buffer));
	}
	replaceAll(userInfo, "\r", "");
	replaceAll(userInfo, "\n", " ");
	return (userInfo);
}

void User::fillUserInfo(const string& userInfo, const string& password) {
	size_t pos = userInfo.find("NICK");
	size_t endPos = userInfo.find(' ', pos + 5);
	if (pos == std::string::npos || endPos == std::string::npos)
		throw InvalidNickException();
	_nickname = userInfo.substr(pos + 5, endPos - (pos + 5));

	//define username
	pos = userInfo.find("USER");
	endPos = userInfo.find(' ', pos + 5);
	if (pos == string::npos || endPos == string::npos)
		throw InvalidUserException();
	_username = userInfo.substr(pos + 5, endPos - (pos + 5));

	//define hostname
	_hostname = userInfo.substr(endPos + 1, userInfo.find(' ', endPos + 1) - (endPos + 1));

	//define fullname
	pos = userInfo.find(':');
	if (pos == string::npos)
		throw InvalideRealnameException();
	endPos = userInfo.find(' ', pos + 1);
	_fullname = userInfo.substr(pos + 1, endPos - (pos + 1));

    //check password
    string user_password;
    pos = userInfo.find("PASS");
    if (pos != string::npos) {
        endPos = userInfo.find(' ', pos + 5);  // \r\n at the end of the pass
        user_password = userInfo.substr(pos + 5, endPos - (pos + 5));
    }
    if (user_password != password)
	{
		sendStringSocket(_clientSocket, ERR_PASSWDMISMATCH(_nickname));
		Server::cout_server(ERR_PASSWDMISMATCH(_nickname));
	}
    else
        _isLogged = true;
}

void User::cout_user(const string & msg) {
	cout << CYAN << "[" << this->_username << "]: "<< msg << RESET;
}

void User::cerr_user(const string & msg) {
	cerr << RED << "[Client]: " << msg << RESET;
}

string & User::getBuffer() {
	return (_buffer);
}

void User::concatBuffer(const string &buffer) {
	_buffer += buffer;
}

void User::clearBuffer() {
	_buffer.clear();
}

