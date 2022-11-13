
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
OBJS_PATH	= ./objs/
SERVER_O	= ${OBJS_PATH}server.o
CLIENT_O	= ${OBJS_PATH}client.o
SERVER_BONUS_O	= ${OBJS_PATH}server_bonus.o
CLIENT_BONUS_O	= ${OBJS_PATH}client_bonus.o

all: lib server client

${OBJS_PATH}%.o: %.c
			@mkdir -p $(OBJS_PATH)
			@cc ${CFLAGS} -c $< -o ${OBJS_PATH}${<:.c=.o}

client:	${CLIENT_O}
			@cc ${CFLAGS} -o client ${CLIENT_O} -L libft -lft

server:	${SERVER_O}
			@cc ${CFLAGS} -o server ${SERVER_O} -L libft -lft

clean:
			@make clean -C libft
			@rm -rf objs

fclean:		clean
			@make fclean -C libft
			@${RM} client server
			@${RM} client_bonus server_bonus

re:			fclean all

bonus:		${SERVER_BONUS_O} ${CLIENT_BONUS_O} lib
			@cc ${CFLAGS} -o server ${SERVER_BONUS_O} -L libft -lft
			@cc ${CFLAGS} -o client ${CLIENT_BONUS_O} -L libft -lft

lib:
			@make -C libft

.PHONY:		all clean fclean re bonus lib
