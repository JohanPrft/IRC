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

	private :
		string			_name;
		string			_topic;
		string			_password;
		int				_maxUser;
		bool			_isTopicProtected;
		bool			_inviteOnly;
		bool			_needPassword;
		bool			_limitUser;
		bool			_topicOperator;

		vector<User*>	_userList;
		vector<User*>	_banList;
		vector<User*> 	_operatorList;
		vector<User*>	_invited;

		Channel();

	public :
		Channel(const string& name, User *owner);
		Channel(const Channel & cpy);
		~Channel();
		Channel &operator=(const Channel & src);


		//getters
		string	getNicksuser(string nickname);
		string	getName() const;
		string	getTopic() const;
		string	getPassword() const;
		int 	getMaxUser() const;
		bool	getIsTopicProtected() const;
		bool	getTopicExist() const;
		bool	getInviteOnly() const;
		bool	getNeedPassword() const;
		bool	getLimitUSer() const;
		int		getUserCount();
		User	*getUser(const string & username);

		vector<User*>	getUserList() const;

		//setters
		void	setTopic(const string& topic);
		void	setIsTopicProtected(bool value);
		void	setPassword(const string& password);
		void 	setMaxUser(int maxUser);
		void	setInviteOnly(bool value);
		void	setNeedPassword(bool value);
		void	setLimitUser(bool value);

		//checkers
		bool    isUserInChannel(User *user);
		bool    isUserOperator(User *user);
		bool    isUserInvited(User *user);
		bool    isUserBanned(User *user);

 		//commands
 		void	addUser(User *user);
 		void	removeUser(User *user);
		void	addOperator(User *user);
		void	removeOperator(User *user);
		void	addBan(User *user);
		void	removeBan(User *user);
		void	addInvited(User *user);
		void	removeInvited(User *user);
		void	printInfo() const;
};

#endif	