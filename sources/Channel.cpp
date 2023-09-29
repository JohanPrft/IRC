#include "../includes/Channel.hpp"


bool	isChannelNameValid(string name)
{
	cout <<"toto" << endl;
	if (name.size() > 50 || name.size() < 2)
		return (false);
	if (name[0] != '&' && name[0] != '#' && name[0] != '+' && name[0] != '!')
		return (false);
	if (name.find(' ') != string::npos || name.find(',') != string::npos)
		return (false);
	return (true);
}


///////// PUBLIC FONCTION OF CLASS CHANNEL ///////////////////

Channel::Channel(string name, string modes, User *owner) :
	_name(name),
	_key("no key"),
	_inviteOnly(false),
	_needKey(false),
	_limitUser(false),
	_maxUser(-1),
	_topic("not define")
{	
}

Channel::Channel(string name, string modes, User *owner, string key) :
	_name(name),
	_key(key),
	_inviteOnly(false),
	_needKey(false),
	_limitUser(false),
	_maxUser(-1),
	_topic("not define")
{	
}

Channel::~Channel()
{
}

void	Channel::init(string modes, User *owner)
{

}

//getters

string	Channel::getName() const
{
	return (_name);
}

string	Channel::getTopic() const
{
	return (_topic);
}

bool	Channel::getNeedKey() const
{
	return (_needKey);
}

bool	Channel::getInviteOnly() const
{
	return (_inviteOnly);
}

bool	Channel::getLimitUSer() const
{
	return (_limitUser);
}



//setters

void	Channel::setKey(string key)
{
	_key = key;
}

void	Channel::setTopic(string topic)
{
	_topic = topic;
}

void	Channel::modifyInvite(bool ok)
{
	_inviteOnly = ok;
}
void	Channel::modifyNeedKey(bool ok)
{
	_needKey = ok;
}
void	Channel::modifyLimitUser(bool ok)
{
	_limitUser = ok;
}



//commands

void	Channel::sendMsgAllUser(User *user, string msg)
{
	for (vector<User *>::iterator it = _userList.begin(); it != _userList.end(); it++)
		if (it->first->getNickname())
			
}

// void Channel::addUser(User *user)
// {


// }

// void	Channel::removeUser(User *user)
// {

// }

// void	Channel::addOperator(User *user)
// {

// }

// void	Channel::removeOperator(User *user)
// {

// }