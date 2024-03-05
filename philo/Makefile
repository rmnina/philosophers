# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 17:00:03 by jdufour           #+#    #+#              #
#    Updated: 2024/03/05 22:25:03 by jdufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = parsing.c \
	main.c \
	utils.c \
	frees.c \
	routine_utils.c \

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -lpthread

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re