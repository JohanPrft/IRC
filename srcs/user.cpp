#include "../includes/user.hpp"

user::user(int socket) :
	_username("not define"),
	_nickname("not define"),
	_userSocket(socket),
	_logged(false)
{
}

user::~user()
{

}

////////////////////////getters/////////////

string	user::getUsername()
{
	return (_username);
}

string	user::getNickname()
{
	return (_nickname);
}

int user::getSocket()
{
	return (_userSocket);
}

bool user::getLogged()
{
	return (_logged);
}

///////////////setters////////////////
void	user::setUsername(string username)
{
	_username = username;
}

void	user::setNickname(string nickname)
{
	_nickname = nickname;
}

void	user::setLogged(bool logged)
{
	_logged = logged;
}
