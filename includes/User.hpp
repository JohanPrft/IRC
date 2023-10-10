#ifndef IRC_USER_HPP
# define IRC_USER_HPP

#include "irc.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>

void put_str_fd(string str, int fd);

class User {

private:
    int		_clientSocket;
	string	_nickname;
	string	_username;
	string	_fullname;
    string	_hostname;
    bool    _isLogged;
  	string _buffer;

	class InvalidNickException : public exception {
		virtual const char *what() const throw() {
			return ("No nickname");
		}
	};

	class InvalidUserException : public exception {
		virtual const char *what() const throw() {
			return ("No username");
		}
	};

class InvalideRealnameException : public exception {
	virtual const char *what() const throw() {
		return ("No realname");
	}
};

public:
	User();
	User(int clientSocket, string password);
	User(const User &src);
	User &operator=(const User &cpy);
	~User();

    int         getSocket() const;
    string getNickname() const;
    string getUsername() const;
    string getFullname() const;
    string getHostname() const;
    int         getIsLogged() const;

    void	setLogged(bool logged);

	string getUserInfo(int clientSocket) const;
	void fillUserInfo(string userInfo, string password);
    void getPassword(string password);

	static void cout_user(const std::string &msg);
	static void cerr_user(const std::string &msg);

};

ostream& operator<<(ostream& os, const User& user);

#endif
