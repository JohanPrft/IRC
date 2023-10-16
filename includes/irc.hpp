#ifndef IRC_HPP
# define IRC_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <poll.h>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <string>
#include <map>
#include <time.h>
#include <sstream>


using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::exception;
using std::vector;
using std::map;
using std::ostream;

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "color.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "utils.hpp"


const string SERVERNAME = "irc.pictochat.net";
const string VERSION = "0.1";
const string USERMODE = "to complete";
const string CHANMODE = "to complete";


// utils

void split(string input, char del, vector<string> &tokens);
#define BUFFER_SIZE 512
const string CRLF = "/r/n";

#endif