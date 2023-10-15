# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 13:29:52 by rlandolt          #+#    #+#              #
#    Updated: 2023/10/15 21:39:46 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

SRC_PATH = ./srcs

SRC = pipex.c \
	$(SRC_PATH)/strings.c \
	$(SRC_PATH)/split.c \
	$(SRC_PATH)/error.c \
	$(SRC_PATH)/path.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		ar -rcs $@ $(OBJ)
		cc -g -o pipex pipex.a -fsanitize=address

all: $(NAME)

bonus: $(NAME_B)

clean:
		rm -f $(OBJ)
		rm -f $(B_OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f $(NAME_B)

re: fclean all

.PHONY: all, bonus, clean, fclean, re
