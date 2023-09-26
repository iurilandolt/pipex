# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 13:29:52 by rlandolt          #+#    #+#              #
#    Updated: 2023/09/26 13:44:48 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

SRC_PATH = ./srcs
FT_PRINTF = $(SRC_PATH)/ft_printf
GNL = $(SRC_PATH)/get_next_line


SRC = pipex.c \
	$(FT_PRINTF)/ft_print_u_nbr.c \
	$(FT_PRINTF)/ft_printchar.c \
	$(FT_PRINTF)/ft_printf.c \
	$(FT_PRINTF)/ft_printhex.c \
	$(FT_PRINTF)/ft_printnbr.c \
	$(FT_PRINTF)/ft_printptr.c \
	$(FT_PRINTF)/ft_printstr.c \
	$(GNL)/get_next_line_bonus.c \
	$(GNL)/get_next_line_utils_bonus.c \

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
