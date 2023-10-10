#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"
#include "replies.hpp"

class Channel;
class User;

class Server {

		public :
			Server(int port, string password, struct tm * timeinfo);
			~Server();

			void	initServer();
			void	initializeServerSocket();
			void	addServerSocketToEvents();

			static void	cout_server(const string & msg);
			static void	cerr_server(const string & msg);

			void 	handleEvents(std::vector<int> &clients);
			void	handleNewConnection(std::vector<int> &clients);
			void 	handleClientDisconnect(std::vector<int> &clients, size_t index);
			void	handleExistingClient(std::vector<int> &clients, size_t index);
      
			void    confirmClientConnection(User *currentClient);
			void	sendMessage(User *currentClient, std::vector<int> &clients);
			void	sendMessageToGroup(User *currentClient, std::vector<int> &clientsFds);
			void	sendMessageToUser(User *currentClient, User *targetClient);
			
		private :
			
			int					_port;
			int					_serverSocket;
			// unsigned			_nbrUserMax;
			// unsigned			_nbrUser;
			std::string			_datetime;
			std::string			_buffer;

	string					_password;
			sockaddr_in				_serverAddress;
			vector<pollfd>			_fds;
			map<int, User*> 		_users;
			// map<string, Channel*>	_channels;
			





};

#endif