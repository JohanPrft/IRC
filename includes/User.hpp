#ifndef IRC_USER_HPP
# define IRC_USER_HPP

#include "irc.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>

void put_str_fd(const string& str, int fd);

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
	User(Server *serv, int clientSocket, const string &password);
	User(const User &src);
	User &operator=(const User &cpy);
	~User();

    int		getSocket() const;
    string	getNickname() const;
    string	getUsername() const;
    string	getFullname() const;
    string	getHostname() const;
    int		getIsLogged() const;
	string & getBuffer();

    void	setLogged(bool logged);
	void	setNickname(const string & nick);
	bool	isNickValidOnConnect(Server *serv, User *user);
	void	setUsername(const string & username);
	void	concatBuffer(const string &buffer);
	void	clearBuffer();

	string getUserInfo(int clientSocket) const;
	void fillUserInfo(const string& userInfo, const string& password);
    void getPassword(string password);

	void cout_user(const std::string &msg);
	static void cerr_user(const std::string &msg);
	static bool isNickValid(Server *serv, User *user, const string &nick, int clientSocket);


};

ostream& operator<<(ostream& os, const User& user);

#endif
