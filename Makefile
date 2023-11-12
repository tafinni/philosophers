# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfinni <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 18:04:41 by tfinni            #+#    #+#              #
#    Updated: 2023/07/29 17:26:45 by tfinni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRC		=	main.c utils.c init.c threads.c checker.c helpers.c
OBJ		=	$(SRC:.c=.o)
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
