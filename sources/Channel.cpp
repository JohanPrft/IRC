#include "../includes/irc.hpp"
#include "../includes/Channel.hpp"

bool	isChannelNameValid(string name)
{
	if (name.size() > 50 || name.size() < 2)
		return (false);
	if (name[0] != '&' && name[0] != '#' && name[0] != '+' && name[0] != '!')
		return (false);
	if (name.find(' ') != string::npos || name.find(',') != string::npos)
		return (false);
	return (true);
}

Channel::Channel() 
{

}

Channel::Channel(const string& name, User *owner) :
 	_name(name),
 	_topic(""),
 	_password("no password"),
 	_maxUser(-1),
	 _isTopicProtected(false),
 	_inviteOnly(false),
 	_needPassword(false),
 	_limitUser(false)
{
	_userList.push_back(owner);
 	_operatorList.push_back(owner);
 	_invited.push_back(owner);
}

Channel::Channel(const Channel &cpy) {
	if (this == &cpy)
		return;
	_name = cpy._name;
	_topic = cpy._topic;
	_password = cpy._password;
	_maxUser = cpy._maxUser;
	_inviteOnly = cpy._inviteOnly;
	_needPassword = cpy._needPassword;
	_limitUser = cpy._limitUser;
	//complete with lists;
}

Channel::~Channel()
{
	
}

//	getters

string	Channel::getNicksuser(string nickname)
{
	(void) nickname;
	string result;
	vector<User *> userlist = getUserList();

	for (vector<User*>::const_iterator it = userlist.begin(); it != userlist.end(); ++it) 
	{
       	User* userPtr = *it;

		if (isUserOperator(userPtr))
			result += "@";
		result += userPtr->getNickname() + " ";
	}

	return result;
}


string	Channel::getName() const {
 	return (_name);
}

string	Channel::getTopic() const {
 	return (_topic);
}

string Channel::getPassword() const {
	return (_password);
}

int Channel::getMaxUser() const {
	return (_maxUser);
}

bool Channel::getIsTopicProtected() const {
	return _isTopicProtected;
}

bool	Channel::getTopicExist() const {
	if (_topic.empty())
		return (false);
	return (true);
}

bool	Channel::getNeedPassword() const {
 	return (_needPassword);
}

bool	Channel::getInviteOnly() const {
 	return (_inviteOnly);
}

bool	Channel::getLimitUSer() const {
 	return (_limitUser);
}

User *Channel::getUser(const string &nickname) {
	for (size_t i = 0; i < _userList.size(); i++)
	{
		if (_userList[i]->getNickname() == nickname)
			return (_userList[i]);
	}
	return (NULL);
}

vector<User *> Channel::getUserList() const {
	return (_userList);
}

int Channel::getUserCount() {
	return (_userList.size());
}

//	setters

void	Channel::setTopic(const string& topic) {
	_topic = topic;
}

void Channel::setIsTopicProtected(bool value) {
	_isTopicProtected = value;
}

void	Channel::setPassword(const string& password) {
 	_password = password;
}

void Channel::setMaxUser(int maxUser) {
	_maxUser = maxUser;
}

void	Channel::setInviteOnly(bool value) {
 	_inviteOnly = value;
}

void	Channel::setNeedPassword(bool value) {
 	_needPassword = value;
}

void	Channel::setLimitUser(bool value) {
	_limitUser = value;
}

//	checkers

bool Channel::isUserInChannel(User *user) {
	if (find(_userList.begin(), _userList.end(), user) != _userList.end())
		return (true);
	return (false);
}

bool Channel::isUserOperator(User *user) {
	if (find(_operatorList.begin(), _operatorList.end(), user) != _operatorList.end())
		return (true);
	return (false);
}

bool Channel::isUserInvited(User *user) {
	if (find(_invited.begin(), _invited.end(), user) != _invited.end())
		return (true);
	return (false);
}

bool Channel::isUserBanned(User *user) {
	if (find(_banList.begin(), _banList.end(), user) != _banList.end())
		return (true);
	return (false);
}

//	commands

//void	Channel::sendMsgAllUser(User *user, string msg)
//{
// 	for (vector<User *>::iterator it = _userList.begin(); it != _userList.end(); it++)
// 		if (user->getNickname() != (*it)->getNickname())
// 			cout<<"utiliesr la fonction send message de la class server"<< endl;
// 	//en attente de la class serveur
//
//}

void Channel::addUser(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

 	if (it != _userList.end())
 		Server::cout_server(user->getNickname() + "is already in the channel");
 	else
		 _userList.push_back(user);
}

void	Channel::removeUser(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);
 	if (it == _userList.end())
		Server::cout_server(user->getNickname() + " is not in the channel");
 	else
 		_userList.erase(it);
}

void	Channel::addOperator(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

 	if (it == _userList.end())
		Server::cout_server(user->getNickname() + " is not in the channel");
 	else
 	{
 		vector<User*>::iterator it = find(_operatorList.begin(), _operatorList.end(), user);

 		if (it != _operatorList.end())
			Server::cout_server(user->getNickname() + " is already an operator");
 		else
 			_operatorList.push_back(user);
 	}
}

void	Channel::removeOperator(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

 	if (it == _userList.end())
		Server::cout_server(user->getNickname() + " is not in the channel");
 	else
 	{
 		vector<User*>::iterator it = find(_operatorList.begin(), _operatorList.end(), user);

 		if (it == _operatorList.end())
			Server::cout_server(user->getNickname() + " is not an operator");
 		else
 			_operatorList.erase(it);
 	}
}

void	Channel::addBan(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

 	if (it == _userList.end())
		Server::cout_server(user->getNickname() + " is not in the channel");
 	else
 	{
 		vector<User*>::iterator it = find(_banList.begin(), _banList.end(), user);

 		if (it != _banList.end())
			Server::cout_server(user->getNickname() + " is already banned");
 		else
 			_banList.push_back(user);
 	}
}

void	Channel::removeBan(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

 	if (it == _userList.end())
		Server::cout_server(user->getNickname() + " is not in the channel");
 	else
 	{
 		vector<User*>::iterator it = find(_banList.begin(), _banList.end(), user);

 		if (it == _banList.end())
			Server::cout_server(user->getNickname() + " is not banned");
 		else
 			_banList.erase(it);
 	}
}

void Channel::addInvited(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

 	if (it != _userList.end())
		Server::cout_server(user->getNickname() + " is already in the channel");
 	else
 	{
 		vector<User*>::iterator it = find(_invited.begin(), _invited.end(), user);

 		if (it != _invited.end())
			Server::cout_server(user->getNickname() + " is already invited");
 		else
 			_invited.push_back(user);
 	}
}

void Channel::removeInvited(User *user)
{
 	vector<User*>::iterator it = find(_userList.begin(), _userList.end(), user);

 	if (it == _userList.end())
		Server::cout_server(user->getNickname() + " is not in the channel");
 	else
 	{
 		vector<User*>::iterator it = find(_invited.begin(), _invited.end(), user);

 		if (it == _invited.end())
			Server::cout_server(user->getNickname() + " is not invited");
 		else
 			_invited.erase(it);
 	}
}

void Channel::printInfo() const{
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Topic: " << _topic << std::endl;
	std::cout << "Password: " << _password << std::endl;
	std::cout << "Max Users: " << _maxUser << std::endl;
	std::cout << "Invite Only: " << (_inviteOnly ? "Yes" : "No") << std::endl;
	std::cout << "Need Password: " << (_needPassword ? "Yes" : "No") << std::endl;
	std::cout << "Limit User: " << (_limitUser ? "Yes" : "No") << std::endl;
}

