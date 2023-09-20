#include "irc.hpp"



class Server {

		public :
			Server(int port, string password);
			~Server();

			void initServer();

		private :
			
			int			_port;
			int			_serverSocket;
			string		_password;
			sockaddr_in	_serverAddress;




};