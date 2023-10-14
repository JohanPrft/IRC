#include "../includes/command.hpp"

void Server::privmsg(User *currentUser, vector<string> args)
{
    //Check errors
    if (args.size() != 3)
    {
        Server::cerr_server("privmsg : not enough parameters !");
        return ;
    }
    // Find user
    string usernameToFind = args[1];
    User *targetUser = NULL;
    std::map<int, User *>::iterator itClient = _users.begin();
    while (itClient != _users.end())
    {
        if(itClient->second->getUsername() == usernameToFind)
            targetUser = itClient->second;
        itClient++;
    }
    if (targetUser == NULL)
        Server::cerr_server(usernameToFind + " is not connected on the server.");
    
    //If user found, send message
    else
        sendMessageToUser(currentUser, targetUser, args[2]);
}

void	ping(int clientSocket, vector<string> splitedCommand)
{
	string pong = "PONG :" + splitedCommand[1];
	Server::cout_server(pong);
	put_str_fd(pong, clientSocket);
	send(clientSocket, pong.c_str(), pong.length(), 0);
}

//!!! Makes weird things: connection becomes unstable (client prompted with welcome, disconnected)
void nick(User *user, vector<string> splitedCommand)
{
	put_str_fd(RPL_NICK(user->getNickname(), splitedCommand[1], user->getUsername(), user->getHostname()), user->getSocket());
	Server::cout_server(RPL_NICK(user->getNickname(), splitedCommand[1], user->getUsername(), user->getHostname()));
	user->setNickname(splitedCommand[1]);
}

void username(User *user, vector<string> splitedCommand)
{
	user->setUsername(splitedCommand[1]);
}
