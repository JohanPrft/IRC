#ifndef IRC_UTILS_HPP
#define IRC_UTILS_HPP

#include "irc.hpp"

void sendStringSocket(int socket, const string& str);
string extractBetween(const string & cmd, const string & str1, const string & str2);

#endif //IRC_UTILS_HPP
