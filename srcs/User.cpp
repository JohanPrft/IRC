#include "User.hpp"

// Intercept and process the first 3 messages
std::string User::receiveInfo(int clientSocket) {
    std::string userInfo;
    for (int i = 0; i < 3; ++i) {
        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead == -1 || bytesRead == 0) {
            std::cerr << "Error reading from client." << std::endl;
            break;
        } else if (bytesRead == 0) {
            // Client disconnected prematurely
            break;
        } else {
            // Process the message
            userInfo += std::string(buffer, bytesRead);
			bzero(buffer, sizeof(buffer));
        }
    }
    return (userInfo);
}

User::User()
{
    _nickname = "Undefined";
    _username = "Undefined";
    _fullname = "Undefined";
    _hostname = "Undefined";
    _clientSocket = -1;
    _isLogged = -1;
}

//register client
User::User(int clientSocket, std::string userInfo) {

    _clientSocket = clientSocket;

    //define nickname
    size_t pos = userInfo.find("NICK");
    size_t endPos = userInfo.find("\n", pos + 5);
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
    endPos = userInfo.find("\n", pos + 1);
    if (pos == std::string::npos)
        throw InvalidUserException();
    _fullname = userInfo.substr(pos + 1, endPos - (pos + 1));
}
//if nick isnt taken
    //send welcome message
//else
    //send error message

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