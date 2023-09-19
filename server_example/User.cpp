#include "User.hpp"

//register client
User::User(std::string nick, std::string user) {
	size_t pos = nick.find("NICK");
	if (pos == std::string::npos)
		throw InvalidNickException();
	_nickname = nick.substr(pos + 5, find(" ", pos + 5));

	pos = user.find("USER");
	if (pos == std::string::npos)
		throw InvalidUserException();
	_username = user.substr(pos + 5, find(" ", pos + 5));

	pos = user.find(":");
	if (pos == std::string::npos)
		throw InvalideRealnameException();
	_fullname = user.substr(pos + 1);
}
//if nick isnt taken
    //send welcome message
//else
    //send error message

User::User(const User &src) {
	*this = src;
}

User &User::operator=(const User &cpy) {
	if (this != &cpy) {

	}
	return (*this);
}

User::~User() {

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
