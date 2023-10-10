#include "../includes/irc.hpp"


void sendStringSocket(int socket, string str)
{
    ssize_t bytesSent = send(socket, str.c_str(), str.length(), 0);
    if (bytesSent == -1)
        cerr << "Error sending data to client" << endl;
}