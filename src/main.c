/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:22:51 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/02/08 15:22:53 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//Singleton, permet d'utiliser une 

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

// Permet de clean à la fin du programme

void	demallocage(struct s_so_long *so_long, t_vars *vars)
{
	int	i;

	i = 0;
	if (so_long)
	{
		if (so_long->map_but_its_a_string_actually)
			free(so_long->map_but_its_a_string_actually);
		if (so_long->map)
			free_array(so_long->map);
		if (so_long->file_fd)
			close(so_long->file_fd);
		while (i != NBR_TXTR)
			free(so_long->txtr[i++]);
		free(so_long);
	}
	// mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	// mlx_destroy_image(vars->mlx, vars->img.img);
	free(vars->mlx);
	exit(0);
}

// Permet d'initialiser les variables de la structure

void	init_so_long(struct s_so_long *so_long, t_vars *vars)
{
	so_long->file_name = NULL;
	so_long->file_fd = 0;
	so_long->map_size = 0;
	so_long->map_x = 0;
	so_long->map_y = 0;
	so_long->map_but_its_a_string_actually = NULL;
	so_long->map = NULL;
	so_long->is_rectangle = 0;
	so_long->x = 0;
	so_long->y = 0;
	so_long->txtr[HERO_TXTR] = ft_strdup("images/hero.xpm");
	so_long->txtr[WALL_TXTR] = ft_strdup("images/wall.xpm");
	so_long->txtr[FLOOR_TXTR] = ft_strdup("images/floor.xpm");
	so_long->txtr[COLLECTIBLE_TXTR] = ft_strdup("images/hero.xpm");
	so_long->txtr[EXIT_TXTR] = ft_strdup("images/hero.xpm");
	so_long->collect_num = 0;
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
	if (last_char(so_long->map_but_its_a_string_actually) == 0
		|| first_char(so_long->map_but_its_a_string_actually) == 0)
		return (-3);
	if (is_supposed_to_be_in_map(so_long) == 0)
		return (-4);
	so_long->map_x = map_width(so_long);
	so_long->map_y = map_height(so_long);
	if (so_long->map_x < 3 || so_long->map_y < 3)
		return (0);
	if (so_long->is_rectangle == 0)
		return (-1);
	so_long->collect_num = cnt_collect(so_long->map_but_its_a_string_actually);
	close(so_long->file_fd);
	so_long->file_fd = open(so_long->file_name, O_RDONLY);
	map_alloc(so_long);
	if (map_filler(so_long) != 1)
		return (-3);
	record_hero(so_long);
	return (1);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//Permet de fermer le programme et de le quitter proprement

int	closing(int keycode, t_vars *vars, struct s_so_long *so_long)
{
	demallocage(so_long, vars);
}

//Permet d'afficher les pixels d'une image

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//Permet d'afficher une texture

void	display_stuff(t_vars *vars, char *str, int x, int y)
{
	int		width;
	int		height;

	width = 0;
	height = 0;
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_xpm_file_to_image(vars->mlx, str, &width, &height);
	if (vars->img.img == NULL)
	{
		printf("xmp lecture has failed\n");
		demallocage(s(), vars);
		exit(0);
	}
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img,
		x * 48, y * 48);

}

//Permet de simplifier la foncion display_map

void	display_simplifyer(t_vars *vars, char c, char *str)
{
	if (s()->map[s()->y][s()->x] == c)
	{

		display_stuff(vars, str, s()->x, s()->y);
	}
}

//Affiche la map de base

int	display_map(t_vars *vars)
{
	s()->x = 0;
	s()->y = 0;

	while (s()->y < s()->map_y)
	{
		while (s()->x < s()->map_x)
		{
			display_simplifyer(vars, WALL, s()->txtr[WALL_TXTR]);
			display_simplifyer(vars, FLOOR, s()->txtr[FLOOR_TXTR]);
			display_simplifyer(vars, COLLECTIBLE, s()->txtr[HERO_TXTR]);
			display_simplifyer(vars, EXIT, s()->txtr[HERO_TXTR]);
			display_stuff(vars, s()->txtr[HERO_TXTR], (s()->hero.x / 48),
				(s()->hero.y / 48));
			s()->x++;
		}
		s()->x = 0;
		s()->y++;
	}
	printf("a");
	return (0);
}

//Permet d'enregistrer les appuis de touches

int	key_hook(int keycode, t_vars *vars)
{
	static int	i;

	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100
		|| keycode == 65307)
	{
		if (keycode == 119)
			if (s()->hero.y > 48
			&& s()->map[(s()->hero.y / 48) - 1][s()->hero.x / 48] != '1')
				{s()->hero.y -= 48;i++;}
		if (keycode == 97)
			if (s()->hero.x > 48
			&& s()->map[(s()->hero.y / 48)][s()->hero.x / 48 - 1] != '1')
				{s()->hero.x -= 48;i++;}
		if (keycode == 115)
			if (s()->hero.y < (s()->map_y * 48) - 96
			&& s()->map[(s()->hero.y / 48) + 1][s()->hero.x / 48] != '1')
				{s()->hero.y += 48;i++;}
		if (keycode == 100)
			if (s()->hero.x < (s()->map_x * 48) - 96
			&& s()->map[(s()->hero.y / 48)][s()->hero.x / 48 + 1] != '1')
				{s()->hero.x += 48;i++;}
		if (keycode == 65307)
			demallocage(s(), vars);
	}
	return (0);
}

//Exécution principale de l'affichage

void	exec(struct s_so_long *so_long, t_vars *vars)
{
	int	x;
	int	y;
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, so_long->map_x * 48,
		so_long->map_y * 48, "so_long");
	vars->img.img = mlx_new_image(vars->mlx, so_long->map_x * 48,
		so_long->map_y * 48);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
		&vars->img.line_length, &vars->img.endian);
	mlx_key_hook(vars->mlx_win, key_hook, &vars);
	mlx_hook(vars->mlx_win, 17, 0, closing, &vars);
	mlx_loop_hook(vars->mlx, display_map, vars);
	if (s()->map[s()->hero.x / 48][s()->hero.y / 48] == COLLECTIBLE)
	{
		display_simplifyer(vars,WALL, s()->txtr[WALL_TXTR]);
		s()->map[s()->hero.x / 48][s()->hero.y / 48] = FLOOR;
		printf("a");
		s()->collect_num = s()->collect_num - 1;
	}

	mlx_loop(vars->mlx);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Gestion des erreurs de map, et si tout se passe bien, le programme avance

void	map_wiring(struct s_so_long *so_long, int i, t_vars *vars)
{
	if (i == 0)
		printf("Error :\nMap too small!\n");
	else if (i == -1)
		printf("Error :\nMap is not rectangle\n");
	else if (i == -2)
		printf("Error :\nFile doesn't exist\n");
	else if (i == -3)
		printf("Error :\nIncorrect map\n");
	else if (i == -4)
		printf("Error :\nIncorrect char found in map\n");
	else
	{
		printf("%s\n", so_long->map_but_its_a_string_actually);
		exec(so_long, vars);
	}
}

// Main, gère certaines erreurs et lance dans le programme les arguments

int	main(int argc, char **argv)
{
	struct s_so_long	*so_long;
	t_vars				*vars;
	int					i;

	if (argc > 1 && argc < 3)
	{
		if (is_dot_ber(argv[1], ".ber") == 1)
		{
			so_long = s();
			if (!so_long)
				return (0);
			vars = malloc(sizeof(t_vars));
			if (!vars)
				return (0);
			i = filler(so_long, argv, vars);
			map_wiring(so_long, i, vars);
			demallocage(so_long, vars);
		}
		else
			printf("Error :\nWrong file type!\n");
	}
	else
		printf("Error :\nArgument number incorrect!\n");
	return (0);
}
