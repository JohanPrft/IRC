#include "User.hpp"

// Intercept and process the first 3 messages

User::User()
{
    _nickname = "Undefined";
    _username = "Undefined";
    _fullname = "Undefined";
    _hostname = "Undefined";
    _clientSocket = -1;
    _isLogged = -1;
}

void put_str_fd(std::string str, int fd)
{
    write(fd, str.c_str(), str.length());
}

//register client
User::User(int clientSocket)
{
    _clientSocket = clientSocket;
    _isLogged = 1;
    char buffer[1024];

    put_str_fd("Welcome to the IRC server!\n", _clientSocket);
    put_str_fd("Please enter your nickname: ", _clientSocket);
    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    recv(_clientSocket, buffer, sizeof(buffer), 0);
    _nickname = buffer;
    _nickname.erase(std::remove(_nickname.begin(), _nickname.end(), '\n'), _nickname.end());

    put_str_fd("Please enter your username: ", _clientSocket);
    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    recv(_clientSocket, buffer, sizeof(buffer), 0);
    _username = buffer;
    _username.erase(std::remove(_username.begin(), _username.end(), '\n'), _username.end());

    put_str_fd("Please enter your fullname: ", _clientSocket);
    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    recv(_clientSocket, buffer, sizeof(buffer), 0);
    _fullname = buffer;
    _fullname.erase(std::remove(_fullname.begin(), _fullname.end(), '\n'), _fullname.end());

    put_str_fd("Please enter your hostname: ", _clientSocket);
    memset(buffer, 0, sizeof(buffer)); // clear the buffer
    recv(_clientSocket, buffer, sizeof(buffer), 0);
    _hostname = buffer;
    _hostname.erase(std::remove(_hostname.begin(), _hostname.end(), '\n'), _hostname.end());

    put_str_fd("You are now registered, welcome!\n", _clientSocket);
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