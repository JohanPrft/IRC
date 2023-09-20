#ifndef IRC_USER_HPP
# define IRC_USER_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>

#include "replies.hpp"

class User {

private:
    int         _clientSocket;
	std::string _nickname;
	std::string _username;
	std::string _fullname;
    std::string _hostname;
    int         _loginStatus;

	class InvalidNickException : public std::exception {
		virtual const char *what() const throw() {
			return ("No nickname");
		}
	};

	class InvalidUserException : public std::exception {
		virtual const char *what() const throw() {
			return ("No username");
		}
	};

class InvalideRealnameException : public std::exception {
	virtual const char *what() const throw() {
		return ("No realname");
	}
};

public:
	User();
	User(int clientSocket, std::string userInfo);
	User(const User &src);
	User &operator=(const User &cpy);
	~User();

    std::string getNickname() const;
    std::string getUsername() const;
    std::string getFullname() const;
    std::string getHostname() const;
    int         getLoginStatus() const;

    static std::string receiveInfo(int clientSocket);
    std::string authConnexion();

};

std::ostream& operator<<(std::ostream& os, const User& user);

#endif
