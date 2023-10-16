#include "../includes/mode.hpp"

void mode(User *user, vector<string> splitedCommand)
{
	splitedCommand.erase(splitedCommand.begin());
	if (splitedCommand.size() == 0)
		{
			sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
			Server::cout_server(ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
			return;
		}


}

void inviteOnly()
{

}

void topic()
{

}

void setChanPassword()
{

}

void makeOperator()
{

}

void limitNumberUser()
{

}