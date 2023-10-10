#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"


class Channel;
class User;

class Server {

		public :
			Server(int port, string password, struct tm * timeinfo);
			~Server();

			void	initServer();
			void	initializeServerSocket();
			void	addServerSocketToEvents();

			void 	handleEvents(vector<int> &clients);
			void	handleNewConnection(vector<int> &clients);
			void 	handleClientDisconnect(vector<int> &clients, size_t index);
			void	handleExistingClient(vector<int> &clients, size_t index);
      
      		void    confirmClientConnection(User *currentClient);
			void	sendMessage(User *currentClient, vector<int> &clients);
			void	sendMessageToGroup(User *currentClient, vector<int> &clientsFds);
			void	sendMessageToUser(User *currentClient, User *targetClient);
			
		private :
			
			int					_port;
			int					_serverSocket;
			// unsigned			_nbrUserMax;
			// unsigned			_nbrUser;
			string			_datetime;

			string					_password;
			sockaddr_in				_serverAddress;
			vector<pollfd>			_fds;
			map<int, User*> 		_users;
			// map<string, Channel*>	_channels;
			





};

#endif