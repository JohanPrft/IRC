#include "User.hpp"

//register client
User::User(string nick, string user) {
	size_t pos = nick.find("NICK");
	if (pos == string::npos)
		throw InvalidNickException();
	_nickname = nick.substr(pos + 5, find(" ", pos + 5));

	pos = user.find("USER");
	if (pos == string::npos)
		throw InvalidUserException();
	_username = user.substr(pos + 5, find(" ", pos + 5));

	pos = user.find(":");
	if (pos == string::npos)
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

string User::getNickname() const {
    return (_nickname);
}

string User::getUsername() const {
    return (_username);
}

string User::getFullname() const {
    return (_fullname);
}

string User::getHostname() const {
    return (_hostname);
}
