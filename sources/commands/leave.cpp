#include "../../includes/irc.hpp"

void	Server::leave(User *user, vector<string> args)
{
    //Check right number of params
    if (args.size() < 2)
    {
        cerr_server("Error : LEAVE : not enough parameters !");
        sendStringSocket(user->getSocket(), ERR_NEEDMOREPARAMS(user->getNickname(), "LEAVE"));
        return ;
    }

    //Check if channel exists
    string channelToFind = args[1];
    Channel *targetChannel = getChannel(channelToFind);
    if (targetChannel == NULL)
    {
        Server::cerr_server(channelToFind + " channel does not exist.");
        sendStringSocket(user->getSocket(), ERR_NOSUCHCHANNEL(user->getNickname(), channelToFind));
        return ;
    }
    
    //Check if user is in the channel
    if (!targetChannel->getUser(user->getNickname()))
    {
        Server::cerr_server(user->getNickname() + " is not connected on the channel.");
        sendStringSocket(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), targetChannel->getName()));
        return ;
    }

    //Remove user from channel
    else
    {
        //check if a reason has been specified
        string reasonOfLeave;
        if (args.size() > 2)
        {
            for (size_t i = 2; i < args.size(); i++)
            reasonOfLeave += " " + args[i];
        }
        else
            reasonOfLeave = "being bored.";

        //Leave channel
        for (size_t i = 0; i < targetChannel->getUserList().size(); i++)
            sendStringSocket(targetChannel->getUserList()[i]->getSocket(), RPL_PART(user_id(user->getNickname(), user->getUsername()), targetChannel->getName(), reasonOfLeave));
        targetChannel->removeUser(user);
        cout_server(user->getNickname() + " has left the channel " + targetChannel->getName() + " for " + reasonOfLeave);
        return ;   
    }
}