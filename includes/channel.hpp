#include "server.hpp"

//  Then, you have to implement the commands that are specific to channel
// operators:
// ∗ KICK - Eject a client from the channel
// ∗ INVITE - Invite a client to a channel
// ∗ TOPIC - Change or view the channel topic
// ∗ MODE - Change the channel’s mode:
// · i: Set/remove Invite-only channel
// · t: Set/remove the restrictions of the TOPIC command to channel
// operators
// · k: Set/remove the channel key (password)
// · o: Give/take channel operator privilege
// · l: Set/remove the user limit to channel


class channel{

	private :
		string			_name;
		string			_topic;
		string			_password;
		int				_maxUser;
		bool			_inviteOnly;

		vector<User*>	_userList;
		vector<string>	_banList;
		vector<string> 	_operatorList;

	public :


};