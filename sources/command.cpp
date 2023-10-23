#include "../includes/command.hpp"

void Server::privmsg(User *currentUser, vector<string> args)
{
    if (args[1][0] != '#')
        privmsgUser(currentUser, args);
    else
        privmsgChannel(currentUser, args);
}

void Server::privmsgChannel(User *currentUser, vector<string> args)
{
    //Check errors
    if (args.size()  < 3)
    {
        Server::cerr_server("Error : PRIVMSG : no text to send");
        sendStringSocket(currentUser->getSocket(), ERR_NOTEXTTOSEND(currentUser->getNickname()));
        return ;
    }
    
    // Find channel
    string channelToFind = args[1];
    Channel *targetChannel = NULL;
    std::map<string, Channel *>::iterator itChannel = _channels.begin();
    while (itChannel != _channels.end())
    {
        if(itChannel->first == channelToFind)
            targetChannel = itChannel->second;
        itChannel++;
    }
    if (targetChannel == NULL)
    {
        Server::cerr_server(channelToFind + " channel does not exist.");
        sendStringSocket(currentUser->getSocket(), ERR_NOSUCHCHANNEL(currentUser->getNickname(), channelToFind));
        return ;
    }

    // Check if user is in channel
    if (!targetChannel->isUserInChannel(currentUser))
    {
        Server::cerr_server(currentUser->getNickname() + " is not in " + channelToFind + " channel.");
        sendStringSocket(currentUser->getSocket(), ERR_CANNOTSENDTOCHAN(currentUser->getNickname(), channelToFind));
        return ;
    }

    //If channel found, send message to all users in channel
    else
    {
        string message;
        for (size_t i = 2; i < args.size(); i++)
            message += " " + args[i];
        sendMessageToChannel(targetChannel, currentUser, message);
    }
}

void Server::privmsgUser(User *currentUser, vector<string> args)
{
    //Check errors
    if (args.size()  < 3)
    {
        Server::cerr_server("Error : PRIVMSG : no text to send");
        sendStringSocket(currentUser->getSocket(), ERR_NOTEXTTOSEND(currentUser->getNickname()));
        return ;
    }
    // Find user
    string nicknameToFind = args[1];
    User *targetUser = NULL;
    std::map<int, User *>::iterator itClient = _users.begin();
    while (itClient != _users.end())
    {
        if(itClient->second->getNickname() == nicknameToFind)
            targetUser = itClient->second;
        itClient++;
    }
    if (targetUser == NULL)
    {
        Server::cerr_server(nicknameToFind + " is not connected on the server.");
        sendStringSocket(currentUser->getSocket(), ERR_NOSUCHNICK(currentUser->getNickname(), nicknameToFind));
        return ;
    }
    //If user found, send message
    else
    {
        string message;
        for (size_t i = 2; i < args.size(); i++)
            message += " " + args[i];
        sendMessageToUser(currentUser, targetUser, message);
    }
}

void ping(int clientSocket, User *user, vector<string> splitedCommand)
{
	sendStringSocket(clientSocket, RPL_PONG(user_id(user->getNickname(), user->getUsername()), splitedCommand[1]));
	user->cout_user(RPL_PONG(user_id(user->getNickname(), user->getUsername()), splitedCommand[1]));
//	put_str_fd(pong, clientSocket);
//	send(clientSocket, pong.c_str(), pong.length(), 0);
}

void nick(Server *serv, User *user, vector<string> splitedCommand)
{
	if (!User::isNickValid(serv, user, splitedCommand[1], user->getSocket()))
		return ;
	sendStringSocket(user->getSocket(), RPL_NICK(user->getNickname(), user->getUsername(), splitedCommand[1]));
	Server::cout_server(RPL_NICK(user->getNickname(), user->getUsername(), splitedCommand[1]));
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


void Server::topic(User *user, vector<string> splitedCommand)
{
	string channel_name = splitedCommand[1];
	string topic = std::accumulate(splitedCommand.begin() + 1, splitedCommand.end(), string());
	if (!channelExist(channel_name))
	{
		sendStringSocket(user->getSocket(),ERR_NOSUCHCHANNEL(user->getNickname(), channel_name));
		return;
	}

	if(!_channels[channel_name]->isUserInChannel(user))
	{
		sendStringSocket(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), channel_name));
		return;
	}
	if (topic.empty())
	{
		if (_channels[channel_name]->getTopic().empty() == false)
			sendStringSocket(user->getSocket(), RPL_TOPIC(user->getNickname(), channel_name, _channels[channel_name]->getTopic()));
		else
			sendStringSocket(user->getSocket(), RPL_NOTOPIC(user->getNickname(), channel_name));	
	}
}