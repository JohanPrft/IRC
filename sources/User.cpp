#include "../includes/irc.hpp"

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

void put_str_fd(string str, int fd)
{
    write(fd, str.c_str(), str.length());
}

//register client
User::User(int clientSocket, string password)
{
    _clientSocket = clientSocket;
    put_str_fd("Welcome to the IRC server!\n", _clientSocket);

	string userInfo = getUserInfo(_clientSocket);
	fillUserInfo(userInfo, password);

    if (_isLogged == false)
    {
        put_str_fd("You aren't logged in, please connect with password\n", _clientSocket);
        while (1);
    }
    put_str_fd("You are now registered, welcome!\n", _clientSocket);
    cout << *this << endl;
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

static bool checkUserInfo(const string userInfo)
{
	if (userInfo.find("NICK") == string::npos)
		return (false);
	else if (userInfo.find("USER") == string::npos)
		return (false);
//	else if (userInfo.find("PASS") == string::npos && userInfo.find("pass") == string::npos) //can be written by user
//		return (false);
	return (true);
}

string User::getUserInfo(int clientSocket) const {
	string userInfo;
	char buffer[1024];
	while (checkUserInfo(userInfo) == false)
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
	return (userInfo);
}

void User::fillUserInfo(string userInfo, string password) {
	size_t pos = userInfo.find("NICK");
	size_t endPos = userInfo.find("\n", pos + 5);
	if (pos == string::npos || endPos == string::npos)
		throw InvalidNickException();
	_nickname = userInfo.substr(pos + 5, endPos - (pos + 5));

	//define username
	pos = userInfo.find("USER");
	endPos = userInfo.find(" ", pos + 5);
	if (pos == string::npos || endPos == string::npos)
		throw InvalidUserException();
	_username = userInfo.substr(pos + 5, endPos - (pos + 5));

	//define hostname
	_hostname = userInfo.substr(endPos + 1, userInfo.find(" ", endPos + 1) - (endPos + 1));

	//define fullname
	pos = userInfo.find(":");
	if (pos == string::npos)
		throw InvalideRealnameException();
	endPos = userInfo.find("\n", pos + 1);
	if (pos == string::npos)
		throw InvalidUserException();
	_fullname = userInfo.substr(pos + 1, endPos - (pos + 1));

    //check password
    string user_password;
    pos = userInfo.find("PASS");
    if (pos != string::npos) {
        endPos = userInfo.find("\r", pos + 5);  // \r\n at the end of the pass
        user_password = userInfo.substr(pos + 5, endPos - (pos + 5));
    }
    if (user_password == password)
        _isLogged = true;
    else
        _isLogged = false;
}