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

			static void	cout_server(const string & msg);
			static void	cerr_server(const string & msg);
  
			void 	handleEvents(vector<int> &clients);
			void	handleNewConnection(vector<int> &clients);
			void 	handleClientDisconnect(vector<int> &clients, size_t index);
			void	handleExistingClient(vector<int> &clients, size_t index);
      
      		void    confirmClientConnection(User *currentClient);
			void	sendMessageToChannel(Channel *currentChannel, User *currentClient, string msg);
			void	sendMessageToUser(User *currentClient, User *targetClient, string msg);


			//	commands
			vector<string> parseCommand(string& command);
			void	receiveCommand(User *currentClient);
			void	sendCommand(int clientSocket, string command, vector<string> args);
			void 	execCommand(User *user, vector<string> splitedCommand);

			
		private :
			
			int					_port;
			int					_serverSocket;
			// unsigned			_nbrUserMax;
			// unsigned			_nbrUser;
			string			_buffer;
			string			_datetime;

			string					_password;
			sockaddr_in				_serverAddress;
			vector<pollfd>			_fds;
			map<int, User*> 		_users;
			map<string, Channel*>	_channels;

			// bool

			bool userExist(string username);
			bool channelExist(string name);
			bool userInChannel(string username, string channel);

			// commands

			void join(User *user, vector<string> args);
			void mode(User *user, vector<string> args);
			void kick(User *user, User *toKick, Channel *channel);

			void privmsg(User *currentUser, vector<string> args);
			void privmsgChannel(User *currentUser, vector<string> args);
			void privmsgUser(User *currentUser, vector<string> args);

};

#endif