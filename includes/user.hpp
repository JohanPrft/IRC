#pragma once
#include "server.hpp"


class user {


		public :
			user(int socket);
			~user();

			string	getUsername();
			string	getNickname();
			int		getSocket();
			bool	getLogged();

			void	setUsername(string username);
			void	setNickname(string nickname);
			void	setLogged(bool logged);


		private :
			string	_username;
			string	_nickname;
			int		_userSocket;
			bool	_logged;






};