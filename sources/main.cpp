#include "../includes/irc.hpp"

int	bad_argument(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "please type : ./irc <port> <password>" << endl;
		return 1;
	}
	int	port = atoi(argv[1]);
	if (port <= 1024 || port >= 65536)
	{
		cout << "port must be between 1024 and 65536" << endl;
		return 1;
	}
	return (0);
}

int main(int argc, char **argv)
{
	// if (bad_argument(argc, argv))
	// 	return 1;
	(void) argc;
	cout << isChannelNameValid(argv[1]) << endl;
	// Server server(atoi(argv[1]), argv[2]);
	// server.initServer();

}