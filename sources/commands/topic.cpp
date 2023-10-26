#include "../../includes/irc.hpp"

void Server::topic(User *user, vector<string> splitedCommand)
{
	string channel_name = splitedCommand[1];
	string topic;
	for (vector<string>::const_iterator it = splitedCommand.begin() + 1; it != splitedCommand.end(); ++it) {
		if (it != splitedCommand.begin() + 1) {
			topic += " ";  // Add a space between elements
		}
		topic += *it;  // Append the element to the topic
	}

	cout << YELLOW << topic << endl;
	if (!channelExist(channel_name))
	{
		sendStringSocket(user->getSocket(),ERR_NOSUCHCHANNEL(user->getNickname(), channel_name));
		return;
	}

	if(!_channels[channel_name]->isUserInChannel(user))
	{
		sendStringSocket(user->getSocket(), ERR_NOTONCHANNEL(user->getNickname(), channel_name));
		return;
	}
	if (topic.empty())
	{
		if (_channels[channel_name]->getTopic().empty() == false)
			sendStringSocket(user->getSocket(), RPL_TOPIC(user->getNickname(), channel_name, _channels[channel_name]->getTopic()));
		else
			sendStringSocket(user->getSocket(), RPL_NOTOPIC(user->getNickname(), channel_name));	
	}
	else 
	{
		if (_channels[channel_name]->getIsTopicProtected() && !(_channels[channel_name]->isUserOperator(user)))
		{
			sendStringSocket(user->getSocket(), ERR_CHANOPRIVSNEEDED(user->getNickname(), channel_name));
			return;
		}
		else
		{
			_channels[channel_name]->setTopic(topic);
			sendMessageToChannel(_channels[channel_name], RPL_TOPIC(user->getNickname(), channel_name, _channels[channel_name]->getTopic()));
		}

	}
}