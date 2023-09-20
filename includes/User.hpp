#ifndef IRC_USER_HPP
# define IRC_USER_HPP

#include "irc.hpp"


class User {

private:
	string _nickname;
	string _username;
	string _fullname;
    string _hostname;

	bool	_logged;
	int		_userSocket;

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
	User(string nick, string user);
	User(const User &src);
	User &operator=(const User &cpy);
	~User();


    string	getNickname() const;
    string	getUsername() const;
    string	getFullname() const;
    string	getHostname() const;
	int		getSocket();
	bool	getLogged();

	void	setLogged(bool logged);
};


#endif
