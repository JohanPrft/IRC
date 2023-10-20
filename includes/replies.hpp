#ifndef IRC_REPLIES_HPP
# define IRC_REPLIES_HPP


# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")

// 001 - Server::sendWelcome
# define RPL_WELCOME(nickName, user, host) ( ":" + SERVERNAME + " 001 " + nickName \
		+ " :Welcome to the Internet Relay Network, " + nickName + "!" + user + "@" + host + "\r\n")

// 002 - Server::sendWelcome
# define RPL_YOURHOST(nickName) ( ":" + SERVERNAME + " 002 " + nickName \
		+ " :Your host is " + SERVERNAME + ", running version " + VERSION + "\r\n")

// 003 - Server::sendWelcome
# define RPL_CREATED(nickName, datetime) ( ":" + SERVERNAME + " 003 " + nickName \
		+ " :This server was created " + datetime + "\r\n")

// 004 - Server::sendWelcome
# define RPL_MYINFO(nickName) ( ":" + SERVERNAME + " 004 " + nickName \
		+ " " + SERVERNAME + " " + VERSION + " " + USERMODE + " " + CHANMODE + "\r\n")

// 221 - MODE
# define RPL_UMODEIS(nickName, userModes) ( ":" + SERVERNAME + " 221 " + nickName \
		+ " :" + userModes + "\r\n")

// 307 - WHOIS
# define RPL_WHOISREGNICK(nickName, userSearched) ( ":" + SERVERNAME + " 307 " + nickName \
		+ " " + userSearched + " :has identified for this nick\r\n")

// 311 - WHOIS
# define RPL_WHOISUSER(nickName, userSearched, userNameSearched, hostSearched, realNameSearched) \
		( ":" + SERVERNAME + " 311 " + nickName + " " + userSearched + " " + userNameSearched \
		+ " " + hostSearched + " :" + realNameSearched + "\r\n")

// 312 - WHOIS
# define RPL_WHOISSERVER(nickName, userSearched, server, serverInfo) \
		( ":" + SERVERNAME + " 312 " + nickName + " " + userSearched + " " + server \
		+ " :" + serverInfo + "\r\n")

// 313 - WHOIS
# define RPL_WHOISOPERATOR(nickName, userSearched) ( ":" + SERVERNAME + " 313 " + nickName \
		+ " " + userSearched + " :is an IRC operator\r\n")

// 318 - WHOIS
# define RPL_ENDOFWHOIS(nickName, userSearched) ( ":" + SERVERNAME + " 318 " + nickName \
		+ " " + userSearched + " :End of /WHOIS list\r\n")

// 319 - WHOIS
# define RPL_WHOISCHANNELS(nickName, userSearched, channels) ( ":" + SERVERNAME + " 319 " + nickName \
		+ " " + userSearched + " :" + channels + "\r\n")

// 378 - WHOIS
# define RPL_WHOISHOST(nickName, userSearched, host) ( ":" + SERVERNAME + " 378 " + nickName \
		+ " " + userSearched + " :is connecting from " + host + "\r\n")

// 379 - WHOIS
# define RPL_WHOISMODES(nickName, userSearched, modes) ( ":" + SERVERNAME + " 379 " + nickName \
		+ " " + userSearched + " :is using modes +" + modes + "\r\n")

// 315 - WHO
# define RPL_ENDOFWHO(nickName, mask) ( ":" + SERVERNAME + " 315 " + nickName + " " \
		+ mask + " :End of WHO list\r\n")

// 322 - LIST
# define RPL_LIST(nickName, channel, nbClient, topic) ( ":" + SERVERNAME + " 322 " + nickName + " " \
		+ channel + " "+ nbClient + " :" + topic + "\r\n")

// 323 - LIST
# define RPL_LISTEND(nickName) ( ":" + SERVERNAME + " 323 " + nickName + " : End of List\r\n")

// 324 - MODE
# define RPL_CHANNELMODEIS(nickName, channel, topic, maxUser, limitUser, needPassword) ( ":" + SERVERNAME + " 324 " + nickName \
		+ " " + channel + " :+" + topic + maxUser + limitUser + needPassword + "\r\n")

// 329 - MODE
# define RPL_CREATIONTIME(nickName, channel, creationTime) ( ":" + SERVERNAME + " 329 " + nickName \
		+ " " + channel + " :" + creationTime + "\r\n")

// 331 - TOPIC
# define RPL_NOTOPIC(nickname, channel) ( ":" + SERVERNAME + " 331 " + nickname + " " \
		+ channel + " :No topic is set\r\n")

// 332 - JOIN - TOPIC
# define RPL_TOPIC(nickName, channel, topic) ( ":" + SERVERNAME + " 332 " + nickName \
		+ " " + channel + " :" + topic + "\r\n")

// 333 - TOPIC
# define RPL_TOPICWHOTIME(nickname, channel, nick_topic, setat) ( ":" + SERVERNAME + " 333 " + nickname + " " \
		+ channel + " " + nick_topic + " " + setat + "\r\n")

// // 341 - INVITE
// # define RPL_INVITING(nickName, invited, channel) ( ":" + SERVERNAME + " 341 " + nickName //add backslash
// 		+ " " + invited + " " + channel + "\r\n")

// 352 - WHO
# define RPL_WHOREPLY(client, nickname, username, realname, host, channel, flags) ( ":" + SERVERNAME \
	+ " 352 " + client + " " + channel + " " + username + " " + host + " " + SERVERNAME + " " \
	+ nickname + " " + flags + " :0 " + realname + "\r\n")

// 353 - JOIN
# define RPL_NAMREPLY(nickName, symbol, channel, names) ( ":" + SERVERNAME + " 353 " + nickName \
		+ " " + symbol + " " + channel + " :" + names + "\r\n")

// 366 - JOIN
# define RPL_ENDOFNAMES(nickName, channel) ( ":" + SERVERNAME + " 366 " + nickName \
		+ " " + channel + " :End of /NAMES list\r\n")

// 367 - MODE
# define RPL_BANLIST(nickName, channel, mask, who, time) ( ":" + SERVERNAME + " 367 " + nickName \
		+ " " + channel + " " + mask + " " + who + " " + time + "\r\n")

// 368 - MODE
# define RPL_ENDOFBANLIST(nickName, channel) ( ":" + SERVERNAME + " 368 " + nickName \
		+ " " + channel + " :End of channel ban list\r\n")

// 372 - MOTD
# define RPL_MOTD(nickName, message) ( ":" + SERVERNAME + " 372 " + nickName \
		+ " : " + message + "\r\n")

// 375 - MOTD
# define RPL_MOTDSTART(nickName) ( ":" + SERVERNAME + " 375 " + nickName \
		+ " :- " + SERVERNAME + " Message of the day - \r\n")

// 376 - MOTD
# define RPL_ENDOFMOTD(nickName) ( ":" + SERVERNAME + " 376 " + nickName \
		+ " :End of MOTD\r\n")

// 381 - OPER
# define RPL_YOUREOPER(nickName) ( ":" + SERVERNAME + " 381 " + nickName \
		+ " :You are now an IRC operator\r\n")

// SPE_CODE - KILL - PING - JOIN
# define RPL_CMD(nickname, user, host, cmd, reply) ( ":" + nickname + "!" + user + "@" + host + " " \
	+ cmd + " " + reply + "\r\n")

// SPE_CODE - NICK
# define RPL_NICK(oldNickname, newNickname, user, host) ( ":" + oldNickname + "!" + user + "@" + host + " NICK " \
	+ newNickname + "\r\n")

// SPE_CODE - MODE
# define RPL_MODE_USER(nickname, user, host, sign, mode) ( ":" + nickname + "!" + user + "@" + host + " MODE " \
	+ nickname + " " + sign + mode + "\r\n")

// SPE_CODE - MODE
# define RPL_MODE_CHANNEL(nickname, user, host, channel, sign, mode) ( ":" + nickname + "!" + user + "@" + host + " MODE " \
	+ channel + " " + sign + mode + "\r\n")

// SPE_CODE - MODE
# define RPL_MODE_CHANNEL_PARAM(nickname, user, host, channel, sign, mode, arg) ( ":" + nickname + "!" + user + "@" + host + " MODE " \
	+ channel + " " + sign + mode + " " + arg + "\r\n")

// SPE_CODE - INVITE
// # define RPL_INVITE(nickname, user, host, channel) ( ":" + nickname + "!" + user + "@" + host + " INVITE " /add backslash
// 	+ nickname + " " + channel + "\r\n")

// SPE_CODE - KICK
# define RPL_KICK(nickname, user, host, channel, kicked, reason) ( ":" + nickname + "!" + user + "@" + host + " KICK " \
	+ channel + " " + kicked + " " + reason + "\r\n")

// SPE_CODE - WALLOPS
# define RPL_WALLOPS(nickname, user, host, text) ( ":" + nickname + "!" + user + "@" + host + " WALLOPS " \
	+ text + "\r\n")

# define RPL_JOIN(user_id, channel) (user_id + " JOIN :" +  channel + "\r\n")

// PRIVMSG
# define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!~" + username + "@localhost PRIVMSG " + target + " " + message + "\r\n")


//INVITE


# define RPL_INVITING(user_id, client, nick, channel) (user_id + " 341 " + client + " " + nick + channel + "\r\n")
# define RPL_INVITE(user_id, invited, channel) (user_id + " INVITE " + invited + channel + "\r\n")



#endif //IRC_REPLIES_HPP