#include "../../includes/irc.hpp"

void	Server::join(User *user, vector<string> args)
{

	if (!isChannelNameValid(args[1]))
		return ;

	Channel *channel;

	if (!channelExist(args[1]))
	{
		channel = new Channel(args[1], user);
		sendStringSocket(user->getSocket(), RPL_JOIN(user_id(user->getNickname(), user->getUsername()), args[1]));
		_channels.insert(std::make_pair(args[1], channel));
		_channels[args[1]]->addOperator(user);
		string	list_of_members = _channels[args[1]]->getNicksuser(user->getNickname());
		sendStringSocket(user->getSocket(), RPL_NAMREPLY(user->getUsername(), args[1], list_of_members));
		sendStringSocket(user->getSocket(), RPL_ENDOFNAMES(user->getUsername(), args[1]));
		sendMessageToChannel(_channels[args[1]], MODE_CHANNELMSGWITHPARAM(_channels[args[1]]->getName(), "+o", user->getNickname()));

	}
	else
	{
		if (_channels[args[1]]->getInviteOnly() && (!_channels[args[1]]->isUserInvited(user)))
		{
			sendStringSocket(user->getSocket(), ERR_INVITEONLYCHAN(user->getNickname(), args[1]));
			return;
		}
		if (_channels[args[1]]->getNeedPassword() && (args.size() < 2 || _channels[args[1]]->getPassword() != args[2]))
		{
			sendStringSocket(user->getSocket(), ERR_BADCHANNELKEY(user->getNickname(), args[1]));
			return;
		}
		//on verifie sit le nombre max de user est atteind
		if (_channels[args[1]]->getMaxUser() && _channels[args[1]]->getMaxUser() != -1
			&& _channels[args[1]]->getUserCount() >= _channels[args[1]]->getMaxUser())
		{
			sendStringSocket(user->getSocket(), ERR_CHANNELISFULL(user->getNickname(), args[1]));
			return;
		}

		
		_channels[args[1]]->addUser(user);
		// sendStringSocket(user->getSocket(), RPL_JOIN(user_id(user->getNickname(), user->getFullname()), args[1]));
		cout << CYAN << user->getNickname() << " join  " << args[1] << WHITE << endl;

		vector<User *> userlist = _channels[args[1]]->getUserList();

		 for (vector<User*>::const_iterator it = userlist.begin(); it != userlist.end(); ++it) 
		 {
       		User* userPtr = *it;
			
			sendStringSocket(userPtr->getSocket(), RPL_JOIN(user_id(user->getNickname(), user->getUsername()), args[1]));
			string	list_of_members = _channels[args[1]]->getNicksuser(user->getNickname());
			sendStringSocket(userPtr->getSocket(), RPL_NAMREPLY(user->getNickname(), args[1], list_of_members));
			sendStringSocket(userPtr->getSocket(), RPL_ENDOFNAMES(user->getNickname(), args[1]));
		 }
		if (_channels[args[1]]->getTopic().empty() == false)
			sendStringSocket(user->getSocket(), RPL_TOPIC(user->getNickname(), args[1], _channels[args[1]]->getTopic()));
	}
}