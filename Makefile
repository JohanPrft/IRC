# ######## VARIABLES ######## #

# ---- Final Executable --- #

NAME			=	ircserv

# ---- Directories ---- #

DIR_OBJS		=	.bin/

DIR_SRCS		=	sources/

DIR_HEADERS		=	includes/

# ---- Files ---- #

HEADERS_LIST	=	irc.hpp			\
					Server.hpp		\
					User.hpp		\
					Channel.hpp		\
					replies.hpp		\
					errors.hpp		\
					utils.hpp		\
					command.hpp		\
					Mode.hpp

SRCS_LIST		=	main.cpp		\
					Server.cpp		\
					User.cpp		\
					Channel.cpp		\
					utils.cpp		\
					Mode.cpp		\
					commands/command.cpp     \
					commands/invite.cpp    \
					commands/join.cpp        \
					commands/kick.cpp		\
					commands/leave.cpp       \
					commands/quit.cpp        \
					commands/privmsg.cpp      \
					commands/topic.cpp        \

HEADERS			=	${HEADERS_LIST:%.hpp=${DIR_HEADERS}%.hpp}

OBJS			=	${SRCS_LIST:%.cpp=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CFLAGS			=	-Wall -Wextra -Werror -g

CPP				=	c++ -std=c++98

# ######## RULES ######## #

all				:	${NAME}

${NAME}			:	${DIR_OBJS} ${OBJS} ${HEADERS}
					${CPP} ${CFLAGS} -I ${DIR_HEADERS} ${OBJS} ${LIBRARY} -o ${NAME}

run				:	${NAME}
					gnome-terminal --tab  -- bash -c "./${NAME} 6667 pass"
					gnome-terminal --tab  -- bash -c "irssi -c localhost -p 6667 -w pass -n bar"
					gnome-terminal --tab  -- bash -c "irssi -c localhost -p 6667 -w pass -n foo"

${OBJS}			:	${DIR_OBJS}%.o:	${DIR_SRCS}%.cpp ${HEADERS} Makefile
					${CPP} ${CFLAGS} -I ${DIR_HEADERS} -c $< -o $@

${DIR_OBJS}		:
					mkdir -p ${DIR_OBJS}
					mkdir -p ${DIR_OBJS}commands

clean			:
					${RM} ${OBJS}

fclean			:	clean
					${RM} -r ${NAME} ${DIR_OBJS}

re				:	fclean all


.PHONY:	all run clean fclean re