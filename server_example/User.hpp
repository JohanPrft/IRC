#ifndef IRC_USER_HPP
# define IRC_USER_HPP

#include <iostream>
#include <string>

class User {

private:
	std::string _nickname;
	std::string _username;
	std::string _realname;

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
	User(std::string infos);
	User(const User &src);
	User &operator=(const User &cpy);
	~User();

};


#endif
