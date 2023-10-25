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

struct tm * initTime() {
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);
	return timeinfo;
}

int main(int argc, char **argv)
{
	if (bad_argument(argc, argv))
		return 1;
	struct tm * timeinfo = initTime();
	signal(SIGINT, handleSignal);

    Server server(atoi(argv[1]), argv[2], timeinfo);
	server.initServer();
}