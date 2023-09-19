#include "User.hpp"

User::User(std::string str) {
	size_t pos = nick.find("NICK");
	if (pos == std::string::npos)
		throw InvalidNickException();
	_nickname = substr(pos + 5, find(" ", pos + 5));

	pos = nick.find("USER");
	if (pos == std::string::npos)
		throw InvalidUserException();
	_username = substr(pos + 5, find(" ", pos + 5));

	pos = nick.find(":");
	if (pos == std::string::npos)
		throw InvalideRealnameException();
	_realname = substr(pos + 1);
}

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
