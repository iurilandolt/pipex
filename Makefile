# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 13:29:52 by rlandolt          #+#    #+#              #
#    Updated: 2024/01/31 12:47:29 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_PATH = ./srcs

SRC = pipex.c \
	$(SRC_PATH)/strings.c \
	$(SRC_PATH)/split.c \
	$(SRC_PATH)/error.c \
	$(SRC_PATH)/path.c \
	$(SRC_PATH)/process.c \

SANITIZER = -g -fsanitize=address

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

debug: CFLAGS += ${SANITIZER}
debug: re

re: fclean all

.PHONY: all, bonus, clean, fclean, re
