#include "../includes/irc.hpp"


void	Server::join(User *user, vector<string> args)
{
	if (args.size() > 2)
		return ;

	if (!isChannelNameValid(args[1]))
		return ;

	Channel *channel;

	if (!channelExist(args[1]))
	{
		channel = new Channel(args[1], user);
		sendStringSocket(user->getSocket(), RPL_JOIN(user_id(user->getNickname(), user->getFullname()), args[1]));
		_channels.insert(std::make_pair(args[1], channel));

	}
	else
	{
		if (_channels[args[1]]->getInviteOnly() && (!_channels[args[1]]->isUserInvited(user)))
			return;
		//on verifie sit le nombre max de user est atteind
		if (_channels[args[1]]->getMaxUser() && _channels[args[1]]->getMaxUser() != -1
			&& _channels[args[1]]->getUserCount() >= _channels[args[1]]->getLimitUSer())
			return;

		
		_channels[args[1]]->addUser(user);
		sendStringSocket(user->getSocket(), RPL_JOIN(user_id(user->getNickname(), user->getFullname()), args[1]));
		user->cout_user(RPL_JOIN(user_id(user->getNickname(), user->getFullname()), args[1]));
	}
	if (_channels[args[1]]->getTopicExist())
	{
		sendStringSocket(user->getSocket(), RPL_TOPIC(user->getNickname(), _channels[args[1]]->getName(), _channels[args[1]]->getTopic()));
		user->cout_user(RPL_TOPIC(user->getNickname(), _channels[args[1]]->getName(), _channels[args[1]]->getTopic()));
	}
}