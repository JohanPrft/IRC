#include "../includes/utils.hpp"

void sendStringSocket(int socket, const string& str)
{
	cout << PURPLE<< "[Server]: Sending : " << str;
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
string extractBetween(const string & cmd, const string & str1, const string & str2)
{
	const size_t len = str1.length();

	size_t pos = cmd.find(str1);
	size_t endPos = cmd.find(str2, pos + len);
	if (pos == std::string::npos || endPos == std::string::npos)
		return "Not found";
	return (cmd.substr(pos + len, endPos - (pos + len)));
}

void replaceAll(string& str, const string& from, const string& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

bool ctrlCPressed = false;

void handleSignal(int signal)
{
	(void)signal;
	ctrlCPressed = true;
}