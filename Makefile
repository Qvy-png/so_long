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
CC = gcc -Wall -Werror -Wextra
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

OBJB = $(BONUS:.c=.o)

BONUS = bonus/main.c\
		bonus/map_alloc.c\
		bonus/map_scan.c\
		bonus/map_scan_utils.c\
		bonus/so_long_utils1.c\
		bonus/ft_itoa.c\
		bonus/init_and_filler.c\
		bonus/displayer.c\
		bonus/hooks.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\

INCL =	includes/get_next_line.h\
		includes/so_long.h\
		ft_printf/

PTF =	ft_printf/ft_printf_nbrs.c\
		ft_printf/ft_printf_charstr.c\
		ft_printf/ft_printf_hex.c\
		ft_printf/ft_printf.c\
		ft_printf/ft_printf_point.c\

all: $(NAME)

%.o: %.c
	@$(CC)  -I/usr/include -Imlx_linux -Ift_printf -O3 -c $< -o $@
		
$(NAME): $(OBJ)
	@echo " \033[0;31mCompiling ft_printf...\033[0m"
	@make -C ft_printf/ -s
	@echo " \033[0;32mSuccess!\033[0m"
	@echo " \033[0;31mCompiling mlx...\033[0m"
	@echo " \033[1;31mWait ...\033[0m"
	@make -C mlx_linux/ -s
	@echo " \033[0;32mSuccess!\033[0m"
	@echo " \033[0;31mCompiling so_long...\033[0m"
	@$(CC) $(OBJ) -g  -Lft_printf -lft_printf -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -o $(NAME) -s
	@echo " \033[0;32mSuccess!\033[0m"

bonus:	$(OBJB)
	@echo " \033[0;31mCompiling so_long bonuses...\033[0m"
	@$(CC) $(OBJB) -g  -Lft_printf -lft_printf -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -o $(NAME) -s
	@echo " \033[0;32mSuccess!\033[0m"

clean:
	@$(RM) -f $(OBJ)
	@$(RM) -f $(OBJB)
	@make fclean -C ft_printf -s
	@make clean -C mlx_linux -s
	@echo " \033[0;32mCleaning done!\033[0m"

fclean: clean
	@$(RM) -f $(NAME) 

re: fclean all

norme:
	@echo " \033[0;31mChecking sources...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(SRC)
	@echo " \033[0;31mChecking ft_printf...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(PTF)
	@echo " \033[0;31mChecking includes...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(INCL)
	@echo " \033[0;32mDone!\033[0m"

sanit:
	@echo " \033[0;31mCompiling ft_printf...\033[0m"
	@make -C ft_printf/ -s
	@echo " \033[0;32mSuccess!\033[0m"
	@echo " \033[0;31mCompiling with fsanitize...\033[0m"
	@$(CC) $(OBJ) -fsanitize=address -g3 -Lft_printf -lft_printf -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -s
	@echo " \033[0;32mSuccess!\033[0m"
.PHONY: clean fclean
