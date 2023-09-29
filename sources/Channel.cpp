#include "../includes/Channel.hpp"

Channel::Channel(string name) :
	_name(name)
{	
}

Channel::~Channel()
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

//setters

void	Channel::setKey(string key)
{
	_key = key;
}

void	Channel::setTopic(string topic)
{
	_topic = topic;
}


//commands

void	Channel::sendMsgAllUser(User * user, string msg)
{

}

void Channel::addUser(User *user)
{


}

void	Channel::removeUser(User *user)
{

}

void	Channel::addOperator(User *user)
{

}

void	Channel::removeOperator(User *user)
{

}