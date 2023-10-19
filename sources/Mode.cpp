/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:05:40 by jprofit           #+#    #+#             */
/*   Updated: 2023/10/19 09:05:40 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Mode.hpp"
#include "../includes/Channel.hpp"

void mode(Server *serv, User *user, vector<string> splitedCommand)
{
    splitedCommand.erase(splitedCommand.begin());
    if (splitedCommand.size() < 2)
    {
        sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
        Server::cout_server(ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
        return;
    }
    string channel = splitedCommand[0];
	string mode = splitedCommand[1];
    Channel *chan = serv->getChannel(channel);
	if (channel == user->getNickname()) //user mode -> ignore
		return;
	if (!chan) //chan doesnt exist
	{
		Server::cout_server("channel not found");
		return;
	}
    if (mode == "+i" || mode == "-i") //invite only
        inviteOnly(serv, chan, user, mode);
    else if (mode == "+t" || mode == "-t") //topic
        topic(serv, chan, user, splitedCommand);
    else if (mode == "+k" || mode == "-k") //password
        setChanPassword(serv, chan, user, splitedCommand);
    else if (mode == "+o" || mode == "-o") //operator
        makeOperator(serv, chan, user, splitedCommand);
    else if (mode == "+l" || mode == "-l") //limit of user
        limitNumberUser(serv, chan, user, splitedCommand);
    else
    {
        sendStringSocket(user->getSocket(), ERR_UMODEUNKNOWNFLAG(user->getNickname()));
        Server::cout_server(ERR_UMODEUNKNOWNFLAG(user->getNickname()));
    }
}

void inviteOnly(Server *serv, Channel *chan, User *user, const string& mode)
{
	(void)serv;
	(void)user;
    if (mode.find('+') != string::npos)
	{
		chan->setInviteOnly(true);
		sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), mode));
		user->cout_user(RPL_UMODEIS(user->getNickname(), mode));
	}
    else if (mode.find('-') != string::npos)
	{
		chan->setInviteOnly(false);
		sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), mode));
		user->cout_user(RPL_UMODEIS(user->getNickname(), mode));
	}
}

void topic(Server *serv, Channel *chan, User *user, vector<string> splitedCommand)
{
	(void)serv;
    if (!chan->isUserOperator(user))
	{
		sendStringSocket(user->getSocket(), ERR_NOPRIVILEGES(user->getNickname()));
		Server::cout_server(ERR_NOPRIVILEGES(user->getNickname()));
		return;
	}
	if (splitedCommand[1].find("+") != string::npos)
	{
		string topic;
		vector<string>::iterator it = splitedCommand.begin();
		it += 2;
		while (it != splitedCommand.end()) {
			topic += *it + " ";
			it++;
		}
		chan->setTopic(topic);
	}
	else if (splitedCommand[1].find("-") != string::npos)
	{
		chan->setTopic("no topic");
	}
	sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
	user->cout_user(RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
}

void setChanPassword(Server *serv, Channel *chan, User *user, vector<string> splitedCommand)
{
	(void)serv;
	if (!chan->isUserOperator(user))
	{
		sendStringSocket(user->getSocket(), ERR_NOPRIVILEGES(user->getNickname()));
		Server::cout_server(ERR_NOPRIVILEGES(user->getNickname()));
		return;
	}
	if (splitedCommand.size() < 2)
	{
		sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
		Server::cout_server(ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
		return;
	}
	if (splitedCommand[1].find("+") != string::npos)
	{
		chan->setNeedPassword(true);
		chan->setPassword(splitedCommand[2]);
	}
	else if (splitedCommand[1].find("-") != string::npos)
	{
		chan->setNeedPassword(false);
		chan->setPassword("no password");
	}
	sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
	user->cout_user(RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
}

void makeOperator(Server *serv, Channel *chan, User *user, vector<string> splitedCommand)
{
	(void)serv;
	if (!chan->isUserOperator(user))
	{
		sendStringSocket(user->getSocket(), ERR_NOPRIVILEGES(user->getNickname()));
		Server::cout_server(ERR_NOPRIVILEGES(user->getNickname()));
		return;
	}
	if (splitedCommand.size() < 2)
	{
		sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
		Server::cout_server(ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
		return;
	}
	vector<string>::iterator it = splitedCommand.begin();
	vector<string>::iterator ite = splitedCommand.begin();
	it++;
	ite += 4;
	if (splitedCommand[1].find("+") != string::npos)
	{
		while (it != splitedCommand.end() && it != ite)
		{
			User *foundUser = chan->getUser(*it);
			if (foundUser)
				chan->addOperator(foundUser);
			it++;
		}
	}
	else if (splitedCommand[1].find("-") != string::npos)
	{
		while (it != splitedCommand.end() && it != ite)
		{
			User *foundUser = chan->getUser(*it);
			if (foundUser)
				chan->removeOperator(foundUser);
			it++;
		}
	}
	sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
	user->cout_user(RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
}

void limitNumberUser(Server *serv, Channel *chan, User *user, vector<string> splitedCommand)
{
	(void)serv;
	if (!chan->isUserOperator(user))
	{
		sendStringSocket(user->getSocket(), ERR_NOPRIVILEGES(user->getNickname()));
		Server::cout_server(ERR_NOPRIVILEGES(user->getNickname()));
		return;
	}
	if (splitedCommand[1].find("+") != string::npos)
	{
		int maxUser = atoi(splitedCommand[2].c_str());
		if (maxUser < 1)
			return;
		chan->setMaxUser(maxUser);
		chan->setLimitUser(true);
	}
	else if (splitedCommand[1].find("-") != string::npos)
	{
		chan->setLimitUser(false);
		chan->setMaxUser(-1);
	}
	sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
	user->cout_user(RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
}