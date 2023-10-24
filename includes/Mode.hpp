#ifndef IRC_MODE_HPP
# define IRC_MODE_HPP

#include "irc.hpp"

class Server;

void inviteOnly(Server *serv, Channel *chan, User *user, const string& mode);
void topic(Server *serv, Channel *chan, vector<string> splitedCommand);
void setChanPassword(Server *serv, Channel *chan, User *user, vector<string> splitedCommand);
void makeOperator(Server *serv, Channel *chan, User *user, vector<string> splitedCommand);
void limitNumberUser(Server *serv, Channel *chan, User *user, vector<string> splitedCommand);
void mode(Server *serv, User *user, vector<string> splitedCommand);


#endif
