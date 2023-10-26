#ifndef IRC_COMMAND_HPP
# define IRC_COMMAND_HPP

#include "irc.hpp"

void    nick(Server *serv, User *user, vector<string> splitedCommand);
void    ping(int clientSocket, User *user, vector<string> splitedCommand);
void	unknown(User *user, vector<string> splitedCommand);

#endif
