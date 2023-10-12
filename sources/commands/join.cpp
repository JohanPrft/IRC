#include "../includes/irc.hpp"


void	Server::join(int clientsocket, vector<string> args)
{
	if (args.size() > 2)
		return ERR_UNKNOWNERROR(client, "JOIN");

	if (!isChannelNameValid(args[0]))
		return ERR_UNKNOWNERROR(client, "JOIN");

	Channel *channel;


}