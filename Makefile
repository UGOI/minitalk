OBJ_DIR = ./objs/

NAME := minitalk
SERVERSRCS := 	server.c
CLIENTSRCS := 	client.c
SERVEROBJFILES := $(SERVERSRCS:.c=.o)
CLIENTOBJFILES := $(CLIENTSRCS:.c=.o)
SERVEROBJ := $(addprefix $(OBJ_DIR), $(SERVEROBJFILES))
CLIENTOBJ := $(addprefix $(OBJ_DIR), $(CLIENTOBJFILES))

BONUS := bonus
BONUS_SERVER_SRCS := server_bonus.c
BONUS_CLIENT_SRCS := client_bonus.c
BONUS_SERVEROBJFILES := $(BONUS_SERVER_SRCS:.c=.o)
BONUS_CLIENTOBJFILES := $(BONUS_CLIENT_SRCS:.c=.o)
BONUS_SERVEROBJ := $(addprefix $(OBJ_DIR), $(BONUS_SERVEROBJFILES))
BONUS_CLIENTOBJ := $(addprefix $(OBJ_DIR), $(BONUS_CLIENTOBJFILES))

SERVER := server
CLIENT := client
CC := cc

CFLAGS ?= -Wall -Wextra -Werror
LIBFTDIR ?= ./libft
LIBFT ?= $(LIBFTDIR)/libft.a

GREEN = \033[1;32m
YEL = \033[1;33m
EOL = \033[0m

$(NAME): lib $(SERVER) $(CLIENT)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(SERVEROBJ)
	@$(CC) $(CFLAGS) $(SERVEROBJ) $(LIBFT) -o $(SERVER)
	@echo "\n$(GREEN) >> Server created.\n $(EOL)"

$(CLIENT): $(CLIENTOBJ)
	@$(CC) $(CFLAGS) $(CLIENTOBJ) $(LIBFT) -o $(CLIENT)
	@echo "\n$(GREEN) >> Client created.\n $(EOL)"

lib:
	@make -C libft
	@echo "\n$(YEL) >> LIBFT created. $(EOL)"

bonus: $(BONUS_SERVEROBJ) $(BONUS_CLIENTOBJ)
	@$(CC) $(CFLAGS) $(BONUS_SERVEROBJ) $(LIBFT) -o $(SERVER)
	@$(CC) $(CFLAGS) $(BONUS_CLIENTOBJ) $(LIBFT) -o $(CLIENT)
	@echo "\n$(GREEN) >> Bonus created.\n $(EOL)"

all: $(NAME)
	@make lib

clean:
	@make clean -C libft
	@rm -rf $(SERVEROBJ) $(CLIENTOBJ) $(BONUS_SERVEROBJ) $(BONUS_CLIENTOBJ)
	@echo "\n$(YEL) >> clean executed. 🗑 \n $(EOL)"

fclean:
	@make fclean -C libft
	@rm -rf $(SERVEROBJ) $(CLIENTOBJ) $(BONUS_SERVEROBJ) $(BONUS_CLIENTOBJ) $(SERVER) $(CLIENT)
	@echo "\n$(YEL) >> fclean executed. 🗑 \n $(EOL)"

re:
	@make fclean
	@make all


.PHONY: clean fclean all re bonus
