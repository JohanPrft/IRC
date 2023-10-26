#include "../../includes/irc.hpp"

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
