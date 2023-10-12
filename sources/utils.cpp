#include "../includes/irc.hpp"


void sendStringSocket(int socket, string str)
{
    ssize_t bytesSent = send(socket, str.c_str(), str.length(), 0);
    if (bytesSent == -1)
        cerr << "Error sending data to client" << endl;
}

void split(string input, char del, vector<string> &tokens)
{
    std::istringstream ss(input);
    string token;
    
    while (std::getline(ss, token, del)) {
        tokens.push_back(token);
    }

    return;
}