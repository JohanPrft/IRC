#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"

class Channel;
class User;

class Server {

		public :
			Server(int port, string password);
			~Server();

			void	initServer();
			void	initializeServerSocket();
			void	addServerSocketToEvents();

			void 	handleEvents(std::vector<int> &clients);
			void	handleNewConnection(std::vector<int> &clients);
			void 	handleClientDisconnect(std::vector<int> &clients, size_t index);
			void	handleExistingClient(std::vector<int> &clients, size_t index);

			void	sendMessageToGroup(User *currentClient, std::vector<int> &clientsFds);
			void	sendMessageToUser(User *currentClient, User *targetClient);
			
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
			





};

#endif