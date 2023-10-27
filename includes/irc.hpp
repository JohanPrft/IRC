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
#include <numeric>
#include <csignal>


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
#include "Mode.hpp"


const string SERVERNAME = "irc.pictochat.net";
const string VERSION = "0.1";
const string USERMODE = "i";
const string CHANMODE = "itkol";


// utils

void split(string input, char del, vector<string> &tokens);
#define BUFFER_SIZE 512
const string CRLF = "/r/n";
const string AUTHORISED_CHAR_NICK = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\|";
extern bool ctrlCPressed;
const string MOTD =
		"                   __                   __                __      \n"
		"        __        /\\ \\__               /\\ \\              /\\ \\__   \n"
		" _____ /\\_\\    ___\\ \\ ,_\\   ___     ___\\ \\ \\___      __  \\ \\ ,_\\  \n"
		"/\\ '__`\\/\\ \\  /'___\\ \\ \\/  / __`\\  /'___\\ \\  _ `\\  /'__`\\ \\ \\ \\/  \n"
		"\\ \\ \\L\\ \\ \\ \\/\\ \\__/\\ \\ \\_/\\ \\L\\ \\/\\ \\__/\\ \\ \\ \\ \\/\\ \\L\\.\\_\\ \\ \\_ \n"
		" \\ \\ ,__/\\ \\_\\ \\____\\\\ \\__\\ \\____/\\ \\____\\\\ \\_\\ \\_\\ \\__/.\\_\\\\ \\__\\\n"
		"  \\ \\ \\/  \\/_/\\/____/ \\/__/\\/___/  \\/____/ \\/_/\\/_/\\/__/\\/_/ \\/__/\n"
		"   \\ \\_\\                                                          \n"
		"    \\/_/                                                          ";


#endif