#ifndef IRC_MACRO_HPP
#define IRC_MACRO_HPP

#define RPL_WELCOME(usr) ("001 " + usr.getNickname() + " :Welcome to the Internet Relay Network " + usr.getNickname() + "!" + usr.getUsername() + "@" + usr.getHostname() + "\r\n")

#endif
