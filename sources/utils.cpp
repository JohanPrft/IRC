#include "../includes/Server.hpp"
#include "../includes/User.hpp"

void sendStringSocket(int socket, std::string str)
{
    ssize_t bytesSent = send(socket, str.c_str(), str.length(), 0);
    if (bytesSent == -1)
        std::cerr << "Error sending data to client" << std::endl;
}