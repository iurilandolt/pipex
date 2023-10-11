# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 13:29:52 by rlandolt          #+#    #+#              #
#    Updated: 2023/10/11 23:28:31 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

NAME_B = pipex_bonus.a

SRC_PATH = ./srcs

SRC = pipex.c \
	$(SRC_PATH)/strings.c \
	$(SRC_PATH)/split.c \
	$(SRC_PATH)/error.c \

B_SRC = pipex_bonus.c \
	$(SRC_PATH)/strings.c \
	$(SRC_PATH)/split.c \
	$(SRC_PATH)/error.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

$(NAME): $(OBJ)
		ar -rcs $@ $(OBJ)
		cc -g -o pipex pipex.a -fsanitize=address

$(NAME_B): $(B_OBJ)
		ar -rcs $@ $(B_OBJ)
		cc -g -o pipex pipex_bonus.a -fsanitize=address

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
