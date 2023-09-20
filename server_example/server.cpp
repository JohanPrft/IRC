#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


/*
 *	Use for server:
 *		make
 *		./server
 *		(server is waiting).
 *
 *	Use for client (another term):
 *		nc localhost 8080
 *		(client is waiting for prompt)
 */

int main(void)
{
	//create a socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET = IPv4, SOCK_STREAM = TCP, 0 = automatic protocol
	if (serverSocket == -1)
	{
		std::cerr << "Error creating socket" << std::endl;
		return 1;
	}

	//bind the socket to an IP / port
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080); //converts to network byte order
	serverAddress.sin_addr.s_addr = INADDR_ANY; //binds to all available interfaces
	if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
	{
		std::cerr << "Error binding socket" << std::endl;
		return 1;
	}

	//put socket into listening mode~
	if (listen(serverSocket, 5) == -1) //backlog max in queue
	{
		std::cerr << "Error listening on socket" << std::endl;
		return 1;
	}
	std::cout << "Listening..." << std::endl;

	//accept a call
	int clientSocket = accept(serverSocket, NULL, NULL); //addr and addr_len unknown
	if (clientSocket == -1)
	{
		std::cerr << "Error accepting client socket" << std::endl;
		return 1;
	}
	std::cout << "Client connected" << std::endl;

	char buffer[1024];
	ssize_t bytesRead;
	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
	{
		std::cout << "Received " << bytesRead << " bytes from client :" << std::endl;
		std::cout.write(buffer, bytesRead);
		bzero(buffer, sizeof(buffer));
	}
	if (bytesRead == -1)
		std::cerr << "Error receiving data from client" << std::endl;

	close(clientSocket);
	close(serverSocket);
	return (0);
}