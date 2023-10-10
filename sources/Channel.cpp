#include "../includes/irc.hpp"


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


// ///////// PUBLIC FONCTION OF CLASS CHANNEL ///////////////////

// Channel::Channel(string name, string modes, User *owner) :
// 	_name(name),
// 	_topic("not define"),
// 	_key("no key"),
// 	_maxUser(-1),
// 	_inviteOnly(false),
// 	_needKey(false),
// 	_limitUser(false)
// {	
// }

// Channel::Channel(string name, string modes, User *owner, string key) :
// 	_name(name),
// 	_topic("not define"),
// 	_key(key),
// 	_maxUser(-1),
// 	_inviteOnly(false),
// 	_needKey(false),
// 	_limitUser(false)
// {	
// }

// Channel::~Channel()
// {
// }

// void	Channel::init(string modes, User *owner)
// {

// }

// //getters

// string	Channel::getName() const
// {
// 	return (_name);
// }

// string	Channel::getTopic() const
// {
// 	return (_topic);
// }

// bool	Channel::getNeedKey() const
// {
// 	return (_needKey);
// }

// bool	Channel::getInviteOnly() const
// {
// 	return (_inviteOnly);
// }

// bool	Channel::getLimitUSer() const
// {
// 	return (_limitUser);
// }



// //setters

// void	Channel::setKey(string key)
// {
// 	_key = key;
// }

// void	Channel::setTopic(string topic)
// {
// 	_topic = topic;
// }

// void	Channel::modifyInvite(bool ok)
// {
// 	_inviteOnly = ok;
// }
// void	Channel::modifyNeedKey(bool ok)
// {
// 	_needKey = ok;
// }
// void	Channel::modifyLimitUser(bool ok)
// {
// 	_limitUser = ok;
// }



// //commands

// void	Channel::sendMsgAllUser(User *user, string msg)
// {
// 	for (vector<User *>::iterator it = _userList.begin(); it != _userList.end(); it++)
// 		if (user->getNickname() != (*it)->getNickname())
// 			cout<<"utiliesr la fonction send message de la class server"<< endl;
// 	//en attente de la class serveur

// }

// void Channel::addUser(User *user)
// {
// 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

// 	if (it != _userList.end())
// 		cout << "this user is already in the channel" << endl;
// 	else
// 		_userList.push_back(user);
// }

// void	Channel::removeUser(User *user)
// {
// 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

// 	if (it == _userList.end())
// 		cout << "this user is not in the channel" << endl;
// 	else
// 		_userList.erase(it);
// }

// void	Channel::addOperator(User *user)
// {
// 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

// 	if (it == _userList.end())
// 		cout << "this user is not in the channel" << endl;
// 	else
// 	{
// 		vector<User*>::iterator it = find(_operatorList.begin(), _operatorList.end(), user);

// 		if (it != _operatorList.end())
// 			cout << "this user is already an operator" << endl;
// 		else
// 			_operatorList.push_back(user);
// 	}
// }

// void	Channel::removeOperator(User *user)
// {
// 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

// 	if (it == _userList.end())
// 		cout << "this user is not in the channel" << endl;
// 	else
// 	{
// 		vector<User*>::iterator it = find(_operatorList.begin(), _operatorList.end(), user);

// 		if (it == _operatorList.end())
// 			cout << "this user is not an operator" << endl;
// 		else
// 			_operatorList.erase(it);
// 	}
// }