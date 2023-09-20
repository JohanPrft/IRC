#ifndef IRC_ERRORS_HPP
#define IRC_ERRORS_HPP

// 401 - KILL - MODE
# define ERR_NOSUCHNICK(client, nickname) ( ":" + SERVERNAME + " 401 " + client + " " \
		+ nickname + " :No such nick/channel\r\n")

// 403 - JOIN - MODE - TOPIC - PART - INVITE - KICK
# define ERR_NOSUCHCHANNEL(client, channel) ( ":" + SERVERNAME + " 403 " + client + " " \
		+ channel + " :No such channel\r\n")

// 403 - JOIN - Variante pour channl name trop long
# define ERR_CHANTOOLONG(client, channel) ( ":" + SERVERNAME + " 403 " + client + " " \
		+ channel + " :Channel name is too long\r\n")

// 404 - PRIVMSG
# define ERR_CANNOTSENDTOCHAN(nickname, channel) ( ":" + SERVERNAME + " 404 " + nickname + " " \
		+ channel + " :Cannot send to channel\r\n")

// 405 - JOIN
# define ERR_TOOMANYCHANNELS(client, channel) ( ":" + SERVERNAME + " 405 " + client + " " \
		+ channel + " :You have joined too many channels\r\n")

// 407 - PRIVMSG
# define ERR_TOOMANYTARGETS(destination) ( ":" + SERVERNAME + " 407 " + destination \
		+ " :Duplicate recipients. No message delivered\r\n")

// 411 - PRIVMSG
# define ERR_NORECIPIENT(client, command) ( ":" + SERVERNAME + " 411 " + client \
		+ " :No recipient given (" + command + ")\r\n")

// 412 - PRIVMSG
# define ERR_NOTEXTTOSEND(client) ( ":" + SERVERNAME + " 412 " + client \
		+ " :No text to send\r\n")

// 421 - Server::_handleCommand
# define ERR_UNKNOWNCOMMAND(client, command) ( ":" + SERVERNAME + " 421 " + client + " " \
		+ command + " :Unknown command\r\n")

// 422 - MOTD
# define ERR_NOMOTD(client) ( ":" + SERVERNAME + " 422 " + client + " :MOTD File is missing\r\n")

// 431 - NICK - JOIN
# define ERR_NONICKNAMEGIVEN(client) ":" + SERVERNAME + " 431 " + client + " :No nickname given\r\n"

// 432 - NICK
# define ERR_ERRONEUSNICKNAME(nickname) ( ":" + SERVERNAME + " 432 " + nickname \
		+ " :Erroneus nickname\r\n")

// 433 - NICK
# define ERR_NICKNAMEINUSE(nickname) ( ":" + SERVERNAME + " 433 " + nickname \
		+ " :Nickname is already in use\r\n")

// 441 - KICK
# define ERR_USERNOTINCHANNEL(nickname, otherNick, channel) ( ":" + SERVERNAME + " 441 " + nickname + " " \
		+ otherNick + " " + channel + " :They aren't on that channel\r\n")

// 442 - TOPIC - PART - INVITE - MODE - KICK
# define ERR_NOTONCHANNEL(nickname, channel) ( ":" + SERVERNAME + " 442 " + nickname + " " \
		+ channel + " :You're not on that channel\r\n")

// 443 - INVITE
# define ERR_USERONCHANNEL(nickname, otherNick, channel) ( ":" + SERVERNAME + " 443 " + nickname + " " \
		+ otherNick + " " + channel + " :is already on channel\r\n")

// 461 - PASS - USER - OPER - MODE - TOPIC - PART - INVITE - KICK
# define ERR_NEEDMOREPARAMS(client, command) (":" +  SERVERNAME + " 461 " + client + " " \
		+ command + " :Not Enough parameters\r\n")

// 462 - PASS
# define ERR_ALREADYREGISTERED(client) ( ":" + SERVERNAME + " 462 " + client \
		+ " :You may not reregister\r\n")

// 464 - PASS - OPER
# define ERR_PASSWDMISMATCH(client) ( ":" + SERVERNAME + " 464 " + client \
		+ " :Password incorrect\r\n")

// 471 - JOIN
# define ERR_CHANNELISFULL(client, channel) ( ":" + SERVERNAME + " 471 " + client \
		+ " " + channel + " :Cannot join channel (+l)\r\n")

// 473 - JOIN
# define ERR_INVITEONLYCHAN(client, channel) ( ":" + SERVERNAME + " 473 " + client \
		+ " " + channel + " :Cannot join channel (+i)\r\n")

// 474 - JOIN
# define ERR_BANNEDFROMCHAN(client, channel) ( ":" + SERVERNAME + " 474 " + client \
		+ " " + channel + " :Cannot join channel (+b)\r\n")

// 475 - JOIN
# define ERR_BADCHANNELKEY(client, channel) ( ":" + SERVERNAME + " 475 " + client \
		+ " " + channel + " :Cannot join channel (+k)\r\n")

// 476 - JOIN
# define ERR_BADCHANMASK(channel) ( ":" + SERVERNAME + " 476 " + channel \
		+ " :Bad Channel Mask\r\n")

// 481 - KILL
# define ERR_NOPRIVILEGES(client) ( ":" + SERVERNAME + " 481 " + client \
		+ " :Permission Denied- You're not an IRC operator\r\n")

// 482 - MODE - TOPIC - KICK
# define ERR_CHANOPRIVSNEEDED(client, channel) ( ":" + SERVERNAME + " 482 " + client \
		+ " " + channel + " :You're not channel operator\r\n")

# define ERR_HALF_CHANOPRIVSNEEDED(client, channel) ( ":" + SERVERNAME + " 482 " + client \
		+ " " + channel + " :You're not (half)channel operator\r\n")

// 491 - OPER
# define ERR_NOOPERHOST(client) ( ":" + SERVERNAME + " 491 " + client \
		+ " :No O-lines for your host\r\n")

// 501 - MODE
# define ERR_UMODEUNKNOWNFLAG(client) ( ":" + SERVERNAME + " 501 " + client \
		+ " :Unknown MODE flag\r\n")

// 502 - MODE
# define ERR_USERSDONTMATCH(client) ( ":" + SERVERNAME + " 502 " + client \
		+ " :Cant change mode for other users\r\n")

// 723 - KILL
// # define ERR_NOPRIVS(client, priv) ( ":" + SERVERNAME + " 723 " + client + " "
// 		+ priv + " :Insufficient oper privileges.\r\n")

// ERROR Message - PASS - KILL
# define ERROR_MESSAGE(reason) ("ERROR :" + reason + "\r\n")

#endif //IRC_ERRORS_HPP
