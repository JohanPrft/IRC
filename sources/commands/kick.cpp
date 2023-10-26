#include "../../includes/irc.hpp"

void Server::kick(User *user, vector<string> args)
{
	//Check enough parameters
    if (args.size() < 3)
    {
        cerr_server("Error : KICK : not enough parameters !");
        sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "KICK"));
        return ;
    }

    //Check if channel exists
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
        sendStringSocket(user->getSocket(), ERR_NOSUCHCHANNEL(user->getNickname(), channelToFind));
        return ;
    }

    //Find targetUser
    string nicknameToFind = args[2];
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
        sendStringSocket(user->getSocket(), ERR_NOSUCHNICK(user->getNickname(), nicknameToFind));
        return ;
    }
    
    //Check if targetUser and User are in the channel
    if (!targetChannel->getUser(targetUser->getNickname()))
    {
        Server::cerr_server(targetUser->getNickname() + " is not in the channel.");
        sendStringSocket(user->getSocket(), ERR_USERNOTINCHANNEL(user->getNickname(), targetUser->getNickname(), targetChannel->getName()));
        return ;
    }
    if (!targetChannel->getUser(user->getNickname()))
    {
        Server::cerr_server(user->getNickname() + " is not connected on the channel.");
        sendStringSocket(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), targetChannel->getName()));
        return ;
    }

    //Check if user has the right to kick
    if (!targetChannel->isUserOperator(user))
    {
        Server::cerr_server(user->getNickname() + " is not operator of " + targetChannel->getName() + " channel.");
        sendStringSocket(user->getSocket(), ERR_CHANOPRIVSNEEDED(user->getNickname(), targetChannel->getName()));
        return ;
    }
    //If everything is checked, kick user from channel
    else
    {
        //check if a reason has been specified
        string reasonOfKick;
        if (args.size() > 4)
        {
            for (size_t i = 3; i < args.size(); i++)
            reasonOfKick += " " + args[i];
        }
        else
            reasonOfKick = "Not respecting the channel's rules.";

        //Kick target user
        for (size_t i = 0; i < targetChannel->getUserList().size(); i++)
            sendStringSocket(targetChannel->getUserList()[i]->getSocket(), RPL_KICK(user_id(user->getNickname(), user->getUsername()), targetChannel->getName(), targetUser->getNickname(), reasonOfKick));
        targetChannel->removeUser(targetUser);
        cout_server(user->getNickname() + " kicked " + targetUser->getNickname() + " of " + targetChannel->getName() + " for " + reasonOfKick);
        return ;   
    }
}