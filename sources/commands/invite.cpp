#include "../../includes/irc.hpp"

void	Server::invite(User *invitator, vector<string> args)
{
	cout << invitator->getNickname() <<endl;
	//verifier que le channel existe
	string channel = args[2];
	if (!channelExist(args[2]))
	{
		sendStringSocket(invitator->getSocket(),ERR_NOSUCHCHANNEL(invitator->getNickname(), channel));
		return;
	}

	//verifier que le user qui invite est bien dans le channel
	if(!_channels[channel]->isUserInChannel(invitator))
	{
		sendStringSocket(invitator->getSocket(), ERR_NOTONCHANNEL(invitator->getNickname(), channel));
		return;
	}

	//verifier que le user existe
	if (!userExist(args[1]))
	{
		sendStringSocket(invitator->getSocket(), ERR_NOSUCHNICK(args[1], channel));
		return;
	}
	User *invitated = userExist(args[1]);

	//verifier que le user n'est pas deja dans le channel
	if(_channels[channel]->isUserInChannel(invitated))
	{
		sendStringSocket(invitator->getSocket(),ERR_USERONCHANNEL(invitator->getNickname(), invitated->getNickname(), channel));
		return;
	}
	//verifier que le user n'est pas ban
	if (_channels[channel]->isUserBanned(invitated))
		return;

	//ajouter le User a la liste des invites
	_channels[channel]->addInvited(invitated);
	sendStringSocket(invitator->getSocket(),RPL_INVITING(user_id(invitator->getNickname(), invitator->getUsername()), invitator->getNickname(), invitated->getNickname(), channel));
	sendStringSocket(invitated->getSocket(),RPL_INVITE(user_id(invitator->getNickname(), invitator->getUsername()), invitated->getNickname(), channel));

}