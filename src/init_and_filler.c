#include "../includes/so_long.h"

// Singleton, permet d'utiliser une structure avec un comportement de variable
// globale. Peut être réutilisée dans toute fonction avec s() au lieu de so_long

struct s_so_long	*s(void)
{
	static struct s_so_long	*s;

	if (!s)
	{
		s = malloc(sizeof(struct s_so_long));
		if (!s)
			return (NULL);
	}
	return (s);
}

// Permet d'initialiser toutes les variables à une valeur de base

void	init_so_long(struct s_so_long *so_long, t_vars *vars)
{
	so_long->file_name = NULL;
	so_long->file_fd = 0;
	so_long->map_size = 0;
	so_long->map_x = 0;
	so_long->map_y = 0;
	so_long->map_string = NULL;
	so_long->map = NULL;
	so_long->is_rectangle = 0;
	so_long->x = 0;
	so_long->y = 0;
	so_long->txtr[HERO_TXTR] = ft_strdup("images/hero.xpm");
	so_long->txtr[WALL_TXTR] = ft_strdup("images/wall.xpm");
	so_long->txtr[FLOOR_TXTR] = ft_strdup("images/floor.xpm");
	so_long->txtr[COLLECTIBLE_TXTR] = ft_strdup("images/collectible.xpm");
	so_long->txtr[EXIT_TXTR] = ft_strdup("images/exit.xpm");
	so_long->collect_num = 0;
	so_long->ex = 0;
	so_long->her = 0;
	so_long->col = 0;
	so_long->steps = 0;
	vars->mlx = NULL;
	vars->addr = NULL;
	vars->img = NULL;
	vars->mlx_win = NULL;
}

// Seconde la fonction filler, permet de faire une extention de cette dernière

void	filler_sec(struct s_so_long *so_long, char **argv, t_vars *vars)
{
	so_long->collect_num = cnt_collect(so_long->map_string);
	close(so_long->file_fd);
	so_long->file_fd = open(so_long->file_name, O_RDONLY);
	map_alloc(so_long);
}

// Permet de faire toute la récupération d'informations dans le fichier
// renvoie un int

int	filler(struct s_so_long *so_long, char **argv, t_vars *vars)
{
	s()->map;
	init_so_long(so_long, vars);
	so_long->file_name = argv[1];
	so_long->file_fd = open(so_long->file_name, O_RDONLY);
	if (so_long->file_fd == -1)
		return (-2);
	map_size(so_long);
	map_to_str(so_long->file_name, so_long);
	if (last_char(so_long->map_string) == 0
		|| first_char(so_long->map_string) == 0)
		return (-3);
	if (is_supposed_to_be_in_map(so_long) == 0)
		return (-4);
	so_long->map_x = map_width(so_long);
	so_long->map_y = map_height(so_long);
	if ((so_long->map_x < 3 && so_long->map_y < 5)
		|| (so_long->map_y < 3 && so_long->map_x < 5))
		return (0);
	if (so_long->is_rectangle == 0)
		return (-1);
	filler_sec(so_long, argv, vars);
	if (map_filler(so_long) != 1)
		return (-3);
	record_hero(so_long);
	return (1);
}
