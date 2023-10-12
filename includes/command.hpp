#ifndef IRC_COMMAND_HPP
# define IRC_COMMAND_HPP

#include "irc.hpp"

void 	nick(User *user, vector<string> splitedCommand);
void 	username(User *user, vector<string> splitedCommand);
void	ping(int clientSocket, vector<string> splitedCommand);

#endif
