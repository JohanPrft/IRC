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

	 		void	init(string modes, User *owner);

	// 		//getters
	 		string	getName() const;
	 		string	getTopic() const;
	 		bool	getNeedKey() const;
	 		bool	getInviteOnly() const;
	 		bool	getLimitUSer() const;
			 User *getUser(const string & username);




	 		//setters
	 		void	setPassword(string password);
	 		void	setTopic(string topic);
	 		void	modifyInvite(bool value);
	 		void	modifyNeedPassword(bool value);
	 		void	modifyLimitUser(bool value);
			 void setMaxUser(int maxUser);

             //checkers
            bool    isUserInChannel(User *user);
            bool    isUserOperator(User *user);
            bool    isUserInvited(User *user);
            bool    isUserBanned(User *user);

	// 		//commands
	// 		void	sendMsgAllUser(User *user, string msg);
	// 		void	addUser(User *user);
	// 		void	removeUser(User *user);

	 		void	addOperator(User *user);
	 		void	removeOperator(User *user);

	// 		void	setMode(string modes);



		


	 private :
	 	string			_name;
	 	string			_topic;
	 	string			_password;
	 	int				_maxUser;

	 	bool			_inviteOnly;
	 	bool			_needPassword;
	 	bool			_limitUser;

	 	vector<User*>	_userList;
	 	vector<User*>	_banList;
	 	vector<User*> 	_operatorList;
	 	vector<User*>	_invited;

	

};

#endif