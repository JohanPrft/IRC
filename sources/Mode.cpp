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
    Channel *chan = serv->getChannel(channel);
	if (!chan) //user mode -> ignore
	{
		Server::cout_server("channel not found");
		return;
	}
    string mode = splitedCommand[1];
	Server::cout_server(channel + " " + mode);
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
        sendStringSocket(user->getSocket(), ERR_UNKNOWNCOMMAND(user->getNickname(), "MODE" + mode));
        Server::cout_server(ERR_UNKNOWNCOMMAND(user->getNickname(), "MODE" + mode));
    }
}

void inviteOnly(Server *serv, Channel *chan, User *user, const string& mode)
{
	(void)serv;
	(void)user;
    if (mode.find('+') != string::npos)
		chan->setInviteOnly(true);
    else if (mode.find('-') != string::npos)
		chan->setInviteOnly(false);
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
	if (splitedCommand[0].find("+") != string::npos)
	{
		string topic;
		vector<string>::iterator it = splitedCommand.begin();
		while (it != splitedCommand.end()) {
			topic += *it + " ";
			it++;
		}
		chan->setTopic(topic);
	}
	else if (splitedCommand[0].find("+") != string::npos)
	{
		chan->setTopic("");
		return;
	}
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
	if (splitedCommand[0].find("+") != string::npos)
	{
		chan->setNeedPassword(true);
		chan->setPassword(splitedCommand[1]);
	}
	else if (splitedCommand[0].find("-") != string::npos)
	chan->setNeedPassword(false);
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
	if (splitedCommand.size() > 4)
		return;
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
	if (splitedCommand[0].find("+") != string::npos)
		chan->setMaxUser(atoi(splitedCommand[1].c_str()));
	else if (splitedCommand[0].find("-") != string::npos)
		chan->setMaxUser(0);
}