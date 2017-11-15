# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 13:04:54 by qmoreaux          #+#    #+#              #
#    Updated: 2017/11/15 11:12:11 by rfernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computorv1

SRC_PATH = ./src/
SRC_NAME = main.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

INC_PATH = ./includes/

LIB_PATH = ./lib/
LIB_NAME = -lft \

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

LIB = $(addprefix -L, $(LIB_PATH))
INC = $(addprefix -I, $(INC_PATH))

CC = gcc
CFLAGS = -Werror -Wall -Wextra

all: $(NAME)

libft:
	make -C lib/libft

$(NAME): $(OBJ)
	make -C lib/Libft
	$(CC) $(LIB) $(LIB_NAME) $(OBJ) -o computorv1

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/op 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make -C lib/Libft/ clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C lib/Libft/ fclean
	rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h
