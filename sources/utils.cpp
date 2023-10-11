#include "../includes/utils.hpp"

void sendStringSocket(int socket, const string& str)
{
    ssize_t bytesSent = send(socket, str.c_str(), str.length(), 0);
    if (bytesSent == -1)
        cerr << "Error sending data to client" << endl;
}

string extractBetween(const string & cmd, const string & str1, const string & str2)
{
	const size_t len = str1.length();

	size_t pos = cmd.find(str1);
	size_t endPos = cmd.find(str2, pos + len);
	if (pos == std::string::npos || endPos == std::string::npos)
		return "Not found";
	return (cmd.substr(pos + len, endPos - (pos + len)));
}