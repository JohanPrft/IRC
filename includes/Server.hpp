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
  
			void 	handleEvents();
			void	handleNewConnection();
			void 	handleClientDisconnect(User *user);
			void	handleExistingClient(User *currentUser);
      
      		void    confirmClientConnection(User *currentClient);
			void	sendMessageToChannel(Channel *currentChannel, User *currentClient, string msg);
			void	sendMessageToChannel(Channel *currentChannel, const string & msg);
			void	sendMessageToUser(User *currentClient, User *targetClient, string msg);

			//getters
			int		getFdUser(User *user);

			//	commands
			vector<string>	parseCommand(string command);
			void			receiveCommand(User *user);
			void			sendCommand(int clientSocket, string command, vector<string> args);
			void			execCommand(User *user, vector<string> splitedCommand);

            //getter
            Channel *getChannel(const string& name);

			// bool
			User * userExist(string username);
			bool channelExist(string name);

private :
			
			int					_port;
			int					_serverSocket;
			string			    _datetime;

			string					_password;
			sockaddr_in				_serverAddress;
			vector<pollfd>			_fds;
			map<int, User*> 		_users;
			map<string, Channel*>	_channels;


			// commands
			void join(User *user, vector<string> args);
			void leave(User *user, vector<string> args);
			void kick(User *user, vector<string> args);
			void invite(User *invitator, vector<string> args);
			void topic(User *user, vector<string> splitedCommand);
			void quit(User *user, vector<string> args);

			void privmsg(User *currentUser, vector<string> args);
			void privmsgChannel(User *currentUser, vector<string> args);
			void privmsgUser(User *currentUser, vector<string> args);

};

#endif