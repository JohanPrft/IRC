#include "../includes/server.hpp"

int	bad_argument(int argc, char **argv)
{
	if (argc != 3)
		return 1;
	
	int	port = atoi(argv[1]);
	if (port == 0)
		return 1;
	return (0);
}

int main(int argc, char **argv)
{
	if (bad_argument(argc, argv))
		return 1;
	(void) argc;
	Server server(atoi(argv[1]), argv[2]);
	server.initServer();

}