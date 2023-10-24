#ifndef IRC_ERRORS_HPP
#define IRC_ERRORS_HPP

# define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command\r\n")

# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters.\r\n")
# define ERR_NOSUCHCHANNEL(client, channel) (":localhost 403 " + client + " " + channel + " :No such channel\r\n")
# define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :The user is not on this channel.\r\n")
# define ERR_USERONCHANNEL(client, nick, channel) (":localhost 443 " + client + " " + nick + " " + channel + " :Is already on channel\r\n")

# define ERR_BANNEDFROMCHAN(client, channel) ("474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")
# define ERR_BADCHANNELKEY(client, channel) ("475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")

# define ERR_USERNOTINCHANNEL(client, nickname, channel) ("441 " + client + " " + nickname + " " + channel + " :They aren't on that channel\r\n")
// # define ERR_CHANOPRIVSNEEDED(client, channel) ("482 " + client + " " +  channel + " :You're not channel operator\r\n")

# define ERR_NOPRIVILEGES(client) ("481 " + client + " :Permission Denied- You're not an IRC operator\r\n")

#define ERR_UMODEUNKNOWNFLAG(client) (":localhost 501 " + client + " :Unknown MODE flag\r\n")
#define ERR_USERSDONTMATCH(client) ("502 " + client + " :Cant change mode for other users\r\n")

#define ERR_CANNOTSENDTOCHAN(client, channel) ("404 " + client + " " + channel + " :Cannot send to channel\r\n")
#define ERR_CHANNELISFULL(client, channel) ("471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_CHANOPRIVSNEEDED(client, channel) (":localhost 482 " + client + " " + channel + " :You're not channel operator\r\n")
#define ERR_INVITEONLYCHAN(client, channel) ("473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_INVALIDMODEPARAM(client, channel, mode, password) ("696 " + client + " " + channel + " " + mode + " " + password + " : password must only contained alphabetic character\r\n")

#define ERR_NOSUCHSERVER(client, servername) (":localhost 402 " + client + " " + servername + " :No such server\r\n")
#define ERR_NOMOTD(client) (":localhost 422 " + client + " :MOTD File is missing\r\n")

# define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :There is no nickname.\r\n")
# define ERR_ERRONEUSNICKNAME(client, nickname) (":localhost 432 " + client + " " + nickname + " :Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(client, nickname) (":localhost 433 " + client + " " + nickname + " :Nickname is already in use.\r\n")

# define ERR_NOOPERHOST(client) ("491 " + client + " :No O-lines for your host\r\n")

# define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect.\r\n")

# define ERR_NOSUCHNICK(client, target) ("401 " + client + " " + target + " :No such nick/channel\r\n")
# define ERR_NORECIPIENT(client) ("411 " + client + " :No recipient given PRIVMSG\r\n")
# define ERR_NOTEXTTOSEND(client) ("412 " + client + " :No text to send\r\n")

# define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not reregister.\r\n")


#endif //IRC_ERRORS_HPP
