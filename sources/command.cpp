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

void	ping(int clientSocket, vector<string> splitedCommand)
{
	string pong = "PONG :" + splitedCommand[1];
	Server::cout_server(pong);
	sendStringSocket(clientSocket, pong);
//	put_str_fd(pong, clientSocket);
//	send(clientSocket, pong.c_str(), pong.length(), 0);
}

void nick(Server *serv, User *user, vector<string> splitedCommand)
{
	if (!User::isNickValid(serv, user, splitedCommand[1], user->getSocket()))
		return ;
	put_str_fd(RPL_NICK(user->getNickname(), user->getNickname(), splitedCommand[1]), user->getSocket());
	Server::cout_server(RPL_NICK(user->getNickname(), user->getNickname(), splitedCommand[1]));
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
