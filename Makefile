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
SRC =	src/main.c\
		src/map_alloc.c\
		src/map_scan.c\
		src/map_scan_utils.c\
		src/so_long_utils1.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\

all: $(NAME)

%.o: %.c
	$(CC)  -I/usr/include -Imlx_linux -O3 -c $< -o $@
		
$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRC)

sanit:
	$(CC) $(OBJ) -fsanitize=address -g3 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

.PHONY: clean fclean
