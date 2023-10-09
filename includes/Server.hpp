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
			map<int, User*> 		_users;
			// map<string, Channel*>	_channels;

			// bool

			bool userExist(string username);
			bool channelExist(string name);
			bool userInChannel(string username, string channel);

			//commands

			// void join(User *user, vector<string> args);
			// void mode(User *user, vector<string> args);
			// void kick(User *user, User *toKick, Channel *channel);

};

#endif