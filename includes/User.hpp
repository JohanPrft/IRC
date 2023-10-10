#ifndef IRC_USER_HPP
# define IRC_USER_HPP

#include "irc.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>

void put_str_fd(std::string str, int fd);

class User {

private:
    int         _clientSocket;
	std::string _nickname;
	std::string _username;
	std::string _fullname;
    std::string _hostname;
    bool        _isLogged;
	std::string _buffer;

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
	User(int clientSocket, std::string password);
	User(const User &src);
	User &operator=(const User &cpy);
	~User();

    int         getSocket() const;
    std::string getNickname() const;
    std::string getUsername() const;
    std::string getFullname() const;
    std::string getHostname() const;
    int         getIsLogged() const;

    void	setLogged(bool logged);

	std::string getUserInfo(int clientSocket) const;
	void fillUserInfo(std::string userInfo, std::string password);
    void getPassword(std::string password);

	static void cout_user(const std::string &msg);
	static void cerr_user(const std::string &msg);

};

std::ostream& operator<<(std::ostream& os, const User& user);

#endif
