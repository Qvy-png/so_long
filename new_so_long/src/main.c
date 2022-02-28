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
	map_filler(so_long);
	return (1);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int	closing(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	static int	i;

	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100
		|| keycode == 65361 || keycode == 65364 || keycode == 65363
		|| keycode == 65362 || keycode == 165307)
	{
		i++;
		printf("%d\n", i);
		mlx_mouse_hide(vars->mlx, vars->win);
	}
	else if (keycode )
		mlx_mouse_show(vars->mlx, vars->win);
	return (0);
}

void	exec(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, closing, &vars);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_loop(vars.mlx);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Gestion des erreurs de map, et si tout se passe bien, le programme avance

void	map_wiring(int i)
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
		exec();
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
			map_wiring(i);
			demallocage(so_long);
		}
		else
			printf("Error :\nWrong file type!\n");
	}
	else
		printf("Error :\nArgument number incorrect!\n");
	return (0);
}
