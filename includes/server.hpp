#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using std::cout;
using std::endl;
using std::string;
using std::cerr;

class Server {

		public :
			Server(int port, string password);
			~Server();

			

		private :
			
			int		_port;
			int		_serverSocket;
			string	_password;



}