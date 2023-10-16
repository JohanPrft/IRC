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
		channel = new Channel(args[1], "test", user);
		_channels.insert(std::make_pair(args[1], channel));
	}
	else
	{
		_channels[args[1]]->addUser(user);
		cout << user->getNickname() << " join  " << args[1] << endl;
	}

}