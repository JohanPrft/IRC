#include "../includes/command.hpp"

void	ping(int clientSocket, vector<string> splitedCommand)
{
	string pong = "PONG :" + splitedCommand[1];
	Server::cout_server(pong);
	put_str_fd(pong, clientSocket);
	send(clientSocket, pong.c_str(), pong.length(), 0);
}

//!!! Makes weird things: connection becomes unstable (client prompted with welcome, disconnected)
void nick(User *user, vector<string> splitedCommand)
{
	put_str_fd(RPL_NICK(user->getNickname(), splitedCommand[1], user->getUsername(), user->getHostname()), user->getSocket());
	Server::cout_server(RPL_NICK(user->getNickname(), splitedCommand[1], user->getUsername(), user->getHostname()));
	user->setNickname(splitedCommand[1]);
}

void username(User *user, vector<string> splitedCommand)
{
	user->setUsername(splitedCommand[1]);
}

void unknown(User *user, vector<string> splitedCommand)
{
	if (splitedCommand.size() == 0)
		return;
	sendStringSocket(user->getSocket(), ERR_UNKNOWNCOMMAND(user->getNickname(), splitedCommand[0]));
	Server::cout_server(ERR_UNKNOWNCOMMAND(user->getNickname(), splitedCommand[0]));
}
