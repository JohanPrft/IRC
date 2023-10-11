#ifndef IRC_COMMAND_HPP
# define IRC_COMMAND_HPP

#include "irc.hpp"

void nick(User *user, const string& cmd);
void username(User *user, const string & cmd);

#endif
