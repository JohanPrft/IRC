#include "../includes/server.hpp"

int main(int argc, char **argv)
{
	// if (bad_argument(argc, argv))
	// 	return 1;
	(void) argc;
	Server server(atoi(argv[1]), argv[2]);
	server.initServer();

}