#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"

class Channel;
class User;

class Server {

		public :
			Server(int port, string password);
			~Server();

			void initServer();

		private :
			
			int					_port;
			int					_serverSocket;
			// unsigned			_nbrUserMax;
			// unsigned			_nbrUser;

			string					_password;
			sockaddr_in				_serverAddress;
			vector<pollfd>			_fds;
			// map<int, User*> 		_users;
			// map<string, Channel*>	_channels;
			





};

#endif