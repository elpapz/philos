# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 23:22:59 by acanelas          #+#    #+#              #
#    Updated: 2023/06/08 05:50:48 by acanelas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = check_input.c\
		execute_philos.c\
		init_args.c\
		printing.c\
		supervision.c\
		utils.c\
		main.c

NAME = philos
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
REMOVE = rm -rf
OBF = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBF)
	$(CC) $(CFLAGS) $(OBF) -o $(NAME)

clean:
	$(REMOVE) $(OBF)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY: all clean fclean re
