# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 13:29:52 by rlandolt          #+#    #+#              #
#    Updated: 2023/09/26 15:15:56 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

SRC_PATH = ./srcs

SRC = pipex.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		ar -rcs $@ $(OBJ)
		cc -g -o pipex pipex.a -fsanitize=address

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re
