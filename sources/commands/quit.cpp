#include "../../includes/irc.hpp"

void	Server::quit(User *user, vector<string> args)
{
    //Check if user is connected to one or multiple channels
    std::map<string, Channel *>::iterator it = _channels.begin();
    while (it != _channels.end())
    {
        if (it->second->isUserInChannel(user))
        {
            //if yes, make him leave the channel
            vector<string> argsLeave;
            argsLeave.push_back("LEAVE");
            argsLeave.push_back(it->second->getName());
            argsLeave.push_back("quiting server");
            leave(user, argsLeave);
        }
        it++;
    }

    //Remove user from server
    
        //Check if a reason has been specified
        string reasonOfQuit;
        if (args.size() > 4)
        {
            for (size_t i = 3; i < args.size(); i++)
            reasonOfQuit += " " + args[i];
        }
        else
            reasonOfQuit = "no reason specified.";
    
    // Disconnect user
    sendStringSocket(user->getSocket(), RPL_QUIT(user_id(user->getNickname(), user->getUsername()), reasonOfQuit));
    cout_server(user->getNickname() + " has quit the server for " + reasonOfQuit);
    handleClientDisconnect(user);
    
    return ;
}
    