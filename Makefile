# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/05 23:13:14 by gostroum          #+#    #+#              #
#    Updated: 2025/10/05 23:13:18 by gostroum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

CLIENT_DEPS = $(CLIENT_OBJS:.o=.d)
SERVER_DEPS = $(SERVER_OBJS:.o=.d)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(NAME_CLIENT)

$(NAME_SERVER): $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(NAME_SERVER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_DEPS) $(SERVER_DEPS)

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

-include $(CLIENT_DEPS) $(SERVER_DEPS)

.PHONY: all clean fclean re
