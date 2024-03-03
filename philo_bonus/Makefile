# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 18:15:43 by jdufour           #+#    #+#              #
#    Updated: 2024/03/02 20:35:29 by jdufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = main.c \
	parsing.c \
	routine_utils.c \
	frees.c \
	utils.c \

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -g3 -Wall -Wextra -Werror

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