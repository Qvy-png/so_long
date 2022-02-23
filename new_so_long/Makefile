# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 09:36:05 by rdel-agu          #+#    #+#              #
#    Updated: 2022/02/22 14:03:02 by rdel-agu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
RM = rm
OBJ = $(SRC:.c=.o)
CFGLAGS = -Wall -Wextra -Werror
SRC =	src/main.c\
		src/map_alloc.c\
		src/map_scan.c\
		src/map_scan_utils.c\
		src/so_long_utils1.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
		
$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -Imlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRC)

.PHONY: clean fclean
