/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:05:40 by jprofit           #+#    #+#             */
/*   Updated: 2023/10/24 14:28:35 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Mode.hpp"
#include "../includes/Channel.hpp"

void mode(Server *serv, User *user, vector<string> splitedCommand)
{
    splitedCommand.erase(splitedCommand.begin());
    string channel = splitedCommand[0];
	string mode = splitedCommand[1];
    Channel *chan = serv->getChannel(channel);
	if (channel == user->getNickname()) //user mode at startup
	{
		if (mode == "+i")
		{
			sendStringSocket(user->getSocket(), MODE_USERMSG(user->getNickname(), mode));
			user->cout_user(MODE_USERMSG(user->getNickname(), mode));
		}
		return;
	}
	if (!chan) //chan doesnt exist
	{
		sendStringSocket(user->getSocket(),  ERR_NOSUCHCHANNEL(user->getNickname(), channel));
		Server::cout_server(ERR_NOSUCHCHANNEL(user->getNickname(), channel));
		return;
	}
	if (!chan->isUserInChannel(user))
	{
		sendStringSocket(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), chan->getName()));
		return;
	}
	if (!chan->isUserOperator(user) && splitedCommand.size() > 1)
	{
		sendStringSocket(user->getSocket(), ERR_CHANOPRIVSNEEDED(user->getNickname(), chan->getName()));
		return;
	}
	if (mode == "+i" || mode == "-i") //invite only
        inviteOnly(serv, chan, user, mode);
    else if (mode == "+t" || mode == "-t") //topic
        topic(serv, chan, splitedCommand);
    else if (mode == "+k" || mode == "-k") //password
        setChanPassword(serv, chan, user, splitedCommand);
    else if (mode == "+o" || mode == "-o") //operator
        makeOperator(serv, chan, user, splitedCommand);
    else if (mode == "+l" || mode == "-l") //limit of user
        limitNumberUser(serv, chan, user, splitedCommand);
    else
    {
		sendStringSocket(user->getSocket(), RPL_CHANNELMODEIS(user->getNickname(), chan->getName(),
		(chan->getTopicExist() ? "t" : "") + (chan->getLimitUSer() ? "l" : "") + (chan->getInviteOnly() ? "i" : "")
		 + (chan->getNeedPassword() ? "k" : "")));
        Server::cout_server(RPL_CHANNELMODEIS(user->getNickname(), chan->getName(),
		(chan->getTopicExist() ? "t" : "") + (chan->getLimitUSer() ? "l" : "") + (chan->getInviteOnly() ? "i" : "")
		+ (chan->getNeedPassword() ? "k" : "")));
    }
}

void inviteOnly(Server *serv, Channel *chan, User *user, const string& mode)
{
	(void)serv;
	(void)user;
    if (mode.find('+') != string::npos && !chan->getInviteOnly())
	{
		chan->setInviteOnly(true);
		sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), mode));
		serv->sendMessageToChannel(chan, MODE_CHANNELMSG(chan->getName(), "+i"));
	}
    else if (mode.find('-') != string::npos && chan->getInviteOnly())
	{
		chan->setInviteOnly(false);
		sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), mode));
		serv->sendMessageToChannel(chan, MODE_CHANNELMSG(chan->getName(), "-i"));
	}
}

string getTopic(vector<string> splitedCommand)
{
	string topic;
	vector<string>::iterator it = splitedCommand.begin();
	it += 2;
	while (it != splitedCommand.end()) {
		topic += *it + " ";
		it++;
	}
	return topic;
}

void topic(Server *serv, Channel *chan, vector<string> splitedCommand)
{
	(void)serv;
	if (splitedCommand[1].find("+") != string::npos && !chan->getIsTopicProtected())
	{
		chan->setIsTopicProtected(true);
		serv->sendMessageToChannel(chan, MODE_CHANNELMSG(chan->getName(), "+t"));
	}
	else if (splitedCommand[1].find("-") != string::npos && chan->getIsTopicProtected())
	{
		chan->setIsTopicProtected(false);
		serv->sendMessageToChannel(chan, MODE_CHANNELMSG(chan->getName(), "-t"));
	}
}

void setChanPassword(Server *serv, Channel *chan, User *user, vector<string> splitedCommand)
{
	if (splitedCommand.size() < 2)
	{
		sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
		return;
	}
	if (splitedCommand[1].find("+") != string::npos && splitedCommand.size() > 2)
	{
		chan->setNeedPassword(true);
		chan->setPassword(splitedCommand[2]);
		serv->sendMessageToChannel(chan, MODE_CHANNELMSG(chan->getName(), "+k"));
	}
	else if (splitedCommand[1].find("-") != string::npos && chan->getNeedPassword() == true)
	{
		chan->setNeedPassword(false);
		chan->setPassword("no password");
		serv->sendMessageToChannel(chan, MODE_CHANNELMSG(chan->getName(), "-k"));
	}
	sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
}

void makeOperator(Server *serv, Channel *chan, User *user, vector<string> splitedCommand)
{
	(void)serv;
	if (splitedCommand.size() < 2)
	{
		sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
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
			{
				if (chan->isUserOperator(foundUser))
					return;
				chan->addOperator(foundUser);
				serv->sendMessageToChannel(chan, MODE_CHANNELMSGWITHPARAM(chan->getName(), "+o", foundUser->getNickname()));
			}
			else
				sendStringSocket(user->getSocket(), ERR_USERNOTINCHANNEL(user->getNickname(), *it, chan->getName()));
			it++;
		}
	}
	else if (splitedCommand[1].find("-") != string::npos)
	{
		while (it != splitedCommand.end() && it != ite)
		{
			User *foundUser = chan->getUser(*it);
			if (foundUser)
			{
				if (!chan->isUserOperator(foundUser))
					return;
				chan->removeOperator(foundUser);
				serv->sendMessageToChannel(chan, MODE_CHANNELMSGWITHPARAM(chan->getName(), "-o", foundUser->getNickname()));
			}
			else
				sendStringSocket(user->getSocket(), ERR_USERNOTINCHANNEL(user->getNickname(), *it, chan->getName()));
			it++;
		}
	}
}

void limitNumberUser(Server *serv, Channel *chan, User *user, vector<string> splitedCommand)
{
	(void)serv;
	if (splitedCommand[1].find("+") != string::npos && splitedCommand.size() > 2)
	{
		int maxUser = atoi(splitedCommand[2].c_str());
		if (maxUser < 1)
			return;
		chan->setMaxUser(maxUser);
		chan->setLimitUser(true);
		serv->sendMessageToChannel(chan, MODE_CHANNELMSGWITHPARAM(chan->getName(), "+l", splitedCommand[2]));
	}
	else if (splitedCommand[1].find("-") != string::npos && chan->getLimitUSer() == true)
	{
		chan->setLimitUser(false);
		chan->setMaxUser(-1);
		serv->sendMessageToChannel(chan, MODE_CHANNELMSG(chan->getName(), "-l"));
	}
	sendStringSocket(user->getSocket(), RPL_UMODEIS(user->getNickname(), splitedCommand[1]));
}
