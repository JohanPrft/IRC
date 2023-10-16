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
		if (_channels[args[1]]->getInviteOnly() && (!_channels[args[1]]->isInvite(user)))
			return;
		channel = new Channel(args[1], "test", user);
		_channels.insert(std::make_pair(args[1], channel));
	}
	else
	{
		//on verifie sit le nombre max de user est atteind
		if (_channels[args[1]]->getLimitUser() && _channels[args[1]]->getLimit() != -1 
			&& _channels[args[1]]->getNbrUser() >= _channels[args[1]]->getLimit())
			return;

		
		_channels[args[1]]->addUser(user);
		send(user)
		cout << CYAN << user->getNickname() << " join  " << args[1] << WHITE << endl;
	}

}