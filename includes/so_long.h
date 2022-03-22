/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:23:11 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/02/08 15:23:13 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define NBR_TXTR 5
# define HERO_TXTR 0
# define WALL_TXTR 1
# define FLOOR_TXTR 2
# define COLLECTIBLE_TXTR 3
# define EXIT_TXTR 4

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <mlx.h>

typedef struct s_vars {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*addr;
}				t_vars;

typedef struct s_hero
{
	int		x;
	int		y;
}				t_hero;

enum
{
	HERO,
	WALL = '1',
	FLOOR = '0',
	COLLECTIBLE = 'C',
	EXIT = 'E'
};

struct s_so_long
{
	char	*file_name;
	int		file_fd;
	int		map_size;
	int		map_x;
	int		map_y;
	char	*map_string;
	char	**map;
	int		is_rectangle;
	t_hero	*hero;
	char	*txtr[NBR_TXTR];
	int		x;
	int		y;
	int		collect_num;
	int		col;
	int		ex;
	int		her;
};

int		last_char(char *str);
int		first_char(char *str);
int		cnt_collect(char *str);
int		display_map(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
int		map_width(struct s_so_long *so_long);
int		map_height(struct s_so_long *so_long);
int		map_filler(struct s_so_long *so_long);
int		is_dot_ber(char *name, char *extention);
int		panic_free(struct s_so_long *so_long, t_vars *vars);
int		is_supposed_to_be_in_map(struct s_so_long *so_long);
int		filler(struct s_so_long *so_long, char **argv, t_vars *vars);
int		closing(int keycode, t_vars *vars, struct s_so_long *so_long);

char	*ft_itoa(int n);
char	*ft_strdup(char *src);

void	free_array(char **twoD);
void	display_map_sec(t_vars *vars);
void	map_size(struct s_so_long *so_long);
void	map_alloc(struct s_so_long *so_long);
void	record_hero(struct s_so_long *so_long);
void	map_tab_filler(struct s_so_long *so_long);
void	exec(struct s_so_long *so_long, t_vars *vars);
void	map_to_str(char *str, struct s_so_long *so_long);
void	display_simplifyer(t_vars *vars, char c, char *str);
void	display_stuff(t_vars *vars, char *str, int x, int y);
void	demallocage(struct s_so_long *so_long, t_vars *vars);
void	map_wiring(struct s_so_long *so_long, int i, t_vars *vars);
void	filler_sec(struct s_so_long *so_long, char **argv, t_vars *vars);

#endif
