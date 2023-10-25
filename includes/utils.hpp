#ifndef IRC_UTILS_HPP
#define IRC_UTILS_HPP

#include "irc.hpp"

void sendStringSocket(int socket, const string& str);
string extractBetween(const string & cmd, const string & str1, const string & str2);
void replaceAll(string& str, const string& from, const string& to);
void handleSignal(int signal);

#endif //IRC_UTILS_HPP
