<<<<<<< HEAD
#include "irc.hpp"

=======
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

using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::vector;
using std::map;
>>>>>>> antoine


class Server {

		public :
			Server(int port, string password);
			~Server();

			void initServer();

		private :
			
			int					_port;
			int					_serverSocket;
			unsigned			_nbrUserMax;
			unsigned			_nbrUser;

			string					_password;
			sockaddr_in				_serverAddress;
			vector<pollfd>			_fds;
			map<int, *user> 		_users;
			map<string, Channel*>	_channels;
			





};