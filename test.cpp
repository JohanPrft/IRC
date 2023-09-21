#include <iostream>
#include <string>

int main() {
    std::string userInfo = "CAP LS\nNICK jojo\nUSER johan johan localhost :Johan";

    size_t pos = userInfo.find("NICK");
    if (pos == std::string::npos)
        return 1;
    size_t endPos = userInfo.find("\n", pos + 5);
    if (endPos == std::string::npos)
        return 1;
    std::string _nickname = userInfo.substr(pos + 5, endPos - (pos + 5));
    std::cout << _nickname << std::endl;

    pos = userInfo.find("USER");
    if (pos == std::string::npos)
        return 1;
    endPos = userInfo.find(" ", pos + 5);
    if (endPos == std::string::npos)
        return 1;
    std::string _username = userInfo.substr(pos + 5, endPos - (pos + 5));
    std::cout << _username << std::endl;

    pos = userInfo.find(":");
    if (pos == std::string::npos)
        return 1;
    endPos = std::string::npos;
    std::string _fullname = userInfo.substr(pos + 1, endPos - (pos + 1));
    std::cout << _fullname << std::endl;

    return 0;
}