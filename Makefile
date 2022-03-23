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
		src/ft_itoa.c\
		src/init_and_filler.c\
		src/displayer.c\
		src/hooks.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\

all: $(NAME)

%.o: %.c
	@$(CC)  -I/usr/include -Imlx_linux -O3 -c $< -o $@
		
$(NAME): $(OBJ)
	@echo " \033[0;31mCompiling mlx...\033[0m"
	@sleep 0.5
	@echo " \033[1;31mWait ...\033[0m"
	@make -C mlx_linux/ -s
	@sleep 0.8
	@echo " \033[0;32mSuccess!\033[0m"
	@echo " \033[0;31mCompiling so_long...\033[0m"
	@$(CC) $(OBJ) -g -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -s
	@sleep 0.5
	@echo " \033[1;31mWait ...\033[0m"
	@sleep 0.8
	@echo " \033[0;32mSuccess!\033[0m"
clean:
	@$(RM) -f $(OBJ)
	@make clean -C mlx_linux -s
	@echo " \033[0;32mCleaning done!\033[0m"

fclean: clean
	@$(RM) -f $(NAME) 

re: fclean all

norme:
	@norminette -R CheckForbiddenSourceHeader $(SRC) 

sanit:
	@echo " Compiling with fsanitize..."
	@$(CC) $(OBJ) -fsanitize=address -g3 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -s
	@echo " Done!"
.PHONY: clean fclean
