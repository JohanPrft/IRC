#include "../../includes/irc.hpp"


void ping(int clientSocket, User *user, vector<string> splitedCommand)
{
	sendStringSocket(clientSocket, RPL_PONG(user_id(user->getNickname(), user->getUsername()), splitedCommand[1]));
	user->cout_user(RPL_PONG(user_id(user->getNickname(), user->getUsername()), splitedCommand[1]));
}

void nick(Server *serv, User *user, vector<string> splitedCommand)
{
	if (splitedCommand.size() < 2) // never true: irssi does the (wrong) job
	{
		sendStringSocket(user->getSocket(), ERR_NONICKNAMEGIVEN(user->getNickname()));
		Server::cout_server(ERR_NONICKNAMEGIVEN(user->getNickname()));
		return ;
	}
	else if (!User::isNickValid(serv, user, splitedCommand[1], user->getSocket()))
		return ;
	sendStringSocket(user->getSocket(), RPL_NICK(user->getNickname(), user->getUsername(), splitedCommand[1]));
	Server::cout_server(RPL_NICK(user->getNickname(), user->getUsername(), splitedCommand[1]));
	user->setNickname(splitedCommand[1]);
}

void unknown(User *user, vector<string> splitedCommand)
{
	if (splitedCommand.size() == 0)
		return;
	sendStringSocket(user->getSocket(), ERR_UNKNOWNCOMMAND(user->getNickname(), splitedCommand[0]));
	Server::cout_server(ERR_UNKNOWNCOMMAND(user->getNickname(), splitedCommand[0]));
}
