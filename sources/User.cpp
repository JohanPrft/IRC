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
}

void put_str_fd(std::string str, int fd)
{
    write(fd, str.c_str(), str.length());
}

//register client
User::User(int clientSocket, std::string password)
{
    _clientSocket = clientSocket;
    put_str_fd("Welcome to the IRC server!\n", _clientSocket);

	std::string userInfo = getUserInfo(_clientSocket);
	fillUserInfo(userInfo, password);

    if (_isLogged == false)
    {
        put_str_fd("You aren't logged in, please connect with password\n", _clientSocket);
        while (1);
    }
    put_str_fd("You are now registered, welcome!\n", _clientSocket);
    std::cout << *this << std::endl;
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

User::~User() {

}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "Nickname: " << user.getNickname() << std::endl;
    os << "Username: " << user.getUsername() << std::endl;
    os << "Fullname: " << user.getFullname() << std::endl;
    os << "Hostname: " << user.getHostname() << std::endl;
    os << "Socket: " << user.getSocket() << std::endl;
    os << "Logged: " << user.getIsLogged() << std::endl;
    return os;
}

std::string User::getNickname() const {
    return (_nickname);
}

std::string User::getUsername() const {
    return (_username);
}

std::string User::getFullname() const {
    return (_fullname);
}

std::string User::getHostname() const {
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

static bool checkUserInfo(const std::string userInfo)
{
	if (userInfo.find("NICK") == std::string::npos)
		return (false);
	else if (userInfo.find("USER") == std::string::npos)
		return (false);
//	else if (userInfo.find("PASS") == std::string::npos && userInfo.find("pass") == std::string::npos) //can be written by user
//		return (false);
	return (true);
}

std::string User::getUserInfo(int clientSocket) const {
	std::string userInfo;
	char buffer[1024];
	while (checkUserInfo(userInfo) == false)
	{
		ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesRead == -1 || bytesRead == 0) {
			std::cerr << "Error reading from client." << std::endl;
			break;
		} else if (bytesRead == 0) {
			// Client disconnected prematurely
			break;
		}
		// Process the message
		userInfo += std::string(buffer, bytesRead);
		bzero(buffer, sizeof(buffer));
	}
	return (userInfo);
}

void User::fillUserInfo(std::string userInfo, std::string password) {
	size_t pos = userInfo.find("NICK");
	size_t endPos = userInfo.find("\r", pos + 5);
	if (pos == std::string::npos || endPos == std::string::npos)
		throw InvalidNickException();
	_nickname = userInfo.substr(pos + 5, endPos - (pos + 5));

	//define username
	pos = userInfo.find("USER");
	endPos = userInfo.find(" ", pos + 5);
	if (pos == std::string::npos || endPos == std::string::npos)
		throw InvalidUserException();
	_username = userInfo.substr(pos + 5, endPos - (pos + 5));

	//define hostname
	_hostname = userInfo.substr(endPos + 1, userInfo.find(" ", endPos + 1) - (endPos + 1));

	//define fullname
	pos = userInfo.find(":");
	if (pos == std::string::npos)
		throw InvalideRealnameException();
	endPos = userInfo.find("\r", pos + 1);
	if (pos == std::string::npos)
		throw InvalidUserException();
	_fullname = userInfo.substr(pos + 1, endPos - (pos + 1));

    //check password
    std::string user_password;
    pos = userInfo.find("PASS");
    if (pos != std::string::npos) {
        endPos = userInfo.find("\r", pos + 5);  // \r\n at the end of the pass
        user_password = userInfo.substr(pos + 5, endPos - (pos + 5));
    }
    if (user_password != password)
        _isLogged = false;
    else
        _isLogged = true;
}