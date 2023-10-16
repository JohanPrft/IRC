#ifndef CHANNEL_HPP
# define CHANNEL_HPP
#include "irc.hpp"

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

template <typename Tc, typename Tk>
bool		containsKey(Tc container, Tk value)
{
	return container.find(value) != container.end();
}


bool	isChannelNameValid(string name);



class user;

class Channel{


	public :

			Channel(string name, string modes, User *owner);
			Channel(string name, string modes, User *owner, string key);
			~Channel();

	// 		void	init(string modes, User *owner);

	// 		//getters
	// 		string	getName() const;
	// 		string	getTopic() const;
	// 		bool	getNeedKey() const;
	// 		bool	getInviteOnly() const;
	// 		bool	getLimitUSer() const;




	// 		//setters
	// 		void	setKey(string key);user
	// 		void	setTopic(string topic);
	// 		void	modifyInvite(bool ok);
	// 		void	modifyNeedKey(bool ok);
	// 		void	modifyLimitUser(bool ok);

	// 		//commands
	// 		void	sendMsgAllUser(User *user, string msg);
			void	addUser(User *user);
	// 		void	removeUser(User *user);

	// 		void	addOperator(User *user);
	// 		void	removeOperator(User *user);

	// 		void	setMode(string modes);



		


	private :
		string			_name;
	// 	string			_topic;
	// 	string			_key;
	// 	int				_maxUser;

	// 	bool			_inviteOnly;
	// 	bool			_needKey;
	// 	bool			_limitUser;

		vector<User*>	_userList;
	// 	vector<User*>	_banList;
		vector<User*> 	_operatorList;
	// 	vector<User*>	_invited;
};

#endif