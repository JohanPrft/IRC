#include "User.hpp"

// 001 - Server::sendWelcome
# define RPL_WELCOME(nickName, user, host) ( ":" + SERVERNAME + " 001 " + nickName \
		+ " :Welcome to the " + SERVERNAME + " Network, " + nickName + "!" + user + "@" + host + "\r\n")

// 002 - Server::sendWelcome
# define RPL_YOURHOST(nickName) ( ":" + SERVERNAME + " 002 " + nickName \
		+ " :Your host is " + SERVERNAME + ", running version " + VERSION + "\r\n")

// 003 - Server::sendWelcome
# define RPL_CREATED(nickName, datetime) ( ":" + SERVERNAME + " 003 " + nickName \
		+ " :This server was created " + datetime + "\r\n")

// 004 - Server::sendWelcome
# define RPL_MYINFO(nickName) ( ":" + SERVERNAME + " 004 " + nickName \
		+ " " + SERVERNAME + " " + VERSION + " " + USERMODE + " " + CHANMODE + "\r\n")

const std::string SERVERNAME = "irc.pictochat.net";
const std::string VERSION = "0.1";
const std::string USERMODE = "to complete";
const std::string CHANMODE = "to complete";

void sendString(int socket, std::string str)
{
	ssize_t bytesSent = send(socket, str.c_str(), str.length(), 0);
	if (bytesSent == -1)
		std::cerr << "Error sending data to client" << std::endl;
}

void User::sendWelcome(User user)
{
	sendString(user.getClientSocket(), RPL_WELCOME(user.getNickname(), user.getUsername(), user.getHostname()));
	sendString(user.getClientSocket(), RPL_YOURHOST(user.getNickname()));
	sendString(user.getClientSocket(), RPL_CREATED(user.getNickname(), "2021-03-01"));
	sendString(user.getClientSocket(), RPL_MYINFO(user.getNickname()));
}

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
    _loginStatus = -1;
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
    _loginStatus = src._loginStatus;
}

User &User::operator=(const User &cpy) {
	if (this != &cpy) {
        _clientSocket = cpy._clientSocket;
        _nickname = cpy._nickname;
        _username = cpy._username;
        _fullname = cpy._fullname;
        _hostname = cpy._hostname;
        _loginStatus = cpy._loginStatus;
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

int User::getLoginStatus() const {
    return (_loginStatus);
}

int User::getClientSocket() const {
	return (_clientSocket);
}