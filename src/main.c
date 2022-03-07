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

// Permet de clean à la fin du programme

void	demallocage(struct s_so_long *so_long)
{
	if (so_long)
	{
		if (so_long->map_but_its_a_string_actually)
			free(so_long->map_but_its_a_string_actually);
		if (so_long->map)
			free_array(so_long->map);
		if (so_long->file_fd)
			close(so_long->file_fd);
		free(so_long);
	}
}

// Permet d'initialiser les variables de la structure

void	init_so_long(struct s_so_long *so_long)
{
	so_long->file_name = NULL;
	so_long->file_fd = 0;
	so_long->map_size = 0;
	so_long->map_x = 0;
	so_long->map_y = 0;
	so_long->map_but_its_a_string_actually = NULL;
	so_long->map = NULL;
	so_long->is_rectangle = 0;
}

// Permet de faire toute la récupération d'informations dans le fichier
// renvoie un int

int	filler(struct s_so_long *so_long, char **argv)
{
	init_so_long(so_long);
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
	close(so_long->file_fd);
	so_long->file_fd = open(so_long->file_name, O_RDONLY);
	map_alloc(so_long);
	if (map_filler(so_long) != 1)
		return (-3);
	record_hero(so_long);
	printf("%d&%d\n\n", so_long->hero.x, so_long->hero.y);
	return (1);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//Permet de fermer le programme et de le quitter proprement

int	closing(int keycode, t_vars *vars, struct s_so_long *so_long)
{
	demallocage(so_long);
	exit(0);
}

//Permet d'afficher les pixels d'une image

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//Permet d'enregistrer les appuis de touches

int	key_hook(int keycode, struct s_so_long *so_long)
{
	static int	i;

	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100
		|| keycode == 65361 || keycode == 65364 || keycode == 65363
		|| keycode == 65362 || keycode == 165307)
		i++;
	if (keycode == 119 || keycode == 65362)
		if (so_long->hero.y > 48 && so_long->map[(so_long->hero.y / 48) - 1][so_long->hero.x / 48] != '1')
			so_long->hero.y -= 48;
	if (keycode == 97 || keycode == 65361)
		if (so_long->hero.x > 48 && so_long->map[(so_long->hero.y / 48)][so_long->hero.x / 48 - 1] != '1')
			so_long->hero.x -= 48;
	if (keycode == 115 || keycode == 65364)
		if (so_long->hero.y < (so_long->map_y * 48) - 96 && so_long->map[(so_long->hero.y / 48) + 1][so_long->hero.x / 48] != '1')
			so_long->hero.y += 48;
	if (keycode == 100 || keycode == 65363)
		if (so_long->hero.x < (so_long->map_x * 48) - 96 && so_long->map[(so_long->hero.y / 48)][so_long->hero.x / 48 + 1] != '1')
			so_long->hero.x += 48;

	if (keycode == 65307)
	{
		demallocage(so_long);
		exit(0);
	}
	printf("%d&%d\n%d\n", so_long->hero.x, so_long->hero.y, i);
	return (0);
}

//Permet d'afficher une texture

void	display_stuff(struct s_so_long *so_long, t_vars vars, char *str, int x, int y)
{
	int		img_width;
	int		img_height;

	img_width = 0;
	img_height = 0;
	vars.img.img = mlx_xpm_file_to_image(vars.mlx, str, &img_width, &img_height);
	if (vars.img.img == NULL)
	{
		printf("xmp lecture has failed\n");
		demallocage(so_long);
		exit(0);
	}
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, x * 48, y * 48);
}

//Affiche la map de base

void display_map(struct s_so_long *so_long, t_vars vars, t_images images, int x, int y)
{
	while (y < so_long->map_y)
	{
		while (x < so_long->map_x)
		{
			if (so_long->map[y][x] == '1')
			{
				display_stuff(so_long, vars, images.wall, x, y);
			}
			if (so_long->map[y][x] == 'C')
			{
				display_stuff(so_long, vars, images.hero, x, y);
			}
			if (so_long->map[y][x] == 'E')
			{
				display_stuff(so_long, vars, images.hero, x, y);
			}
			if (so_long->map[y][x] == '0')
			{
				display_stuff(so_long, vars, images.floor, x, y);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

//Exécution principale de l'affichage

void	exec(struct s_so_long *so_long)
{
	t_vars	vars;
	t_images images;

	images.wall = ft_strdup("images/wall.xpm");
	images.hero = ft_strdup("images/hero.xpm");
	images.floor = ft_strdup("images/floor.xpm");
	int	x;
	int	y;

	x = 0;
	y = 0;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, so_long->map_x * 48, so_long->map_y * 48, "Hello world!");
	vars.img.img = mlx_new_image(vars.mlx, so_long->map_x * 48, so_long->map_y * 48);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
								&vars.img.endian);
	display_map(so_long, vars, images, x, y);
	mlx_key_hook(vars.mlx_win, key_hook, so_long);
	mlx_hook(vars.mlx_win, 17, 0, closing, &vars);
	display_stuff(so_long, vars, images.hero, so_long->hero.x, so_long->hero.y);
	mlx_loop(vars.mlx);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Gestion des erreurs de map, et si tout se passe bien, le programme avance

void	map_wiring(struct s_so_long *so_long, int i)
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
		exec(so_long);
	}
}

// Main, gère certaines erreurs et lance dans le programme les arguments

int	main(int argc, char **argv)
{
	struct s_so_long	*so_long;
	int					i;

	if (argc > 1 && argc < 3)
	{
		if (is_dot_ber(argv[1], ".ber") == 1)
		{
			so_long = malloc(sizeof(struct s_so_long));
			if (so_long == NULL)
				return (0);
			i = filler(so_long, argv);
			map_wiring(so_long, i);
			demallocage(so_long);
		}
		else
			printf("Error :\nWrong file type!\n");
	}
	else
		printf("Error :\nArgument number incorrect!\n");
	return (0);
}
