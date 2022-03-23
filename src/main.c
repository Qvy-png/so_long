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

int	demallocage(t_vars *vars)
{
	int	i;

	i = 0;
	if (s() && s()->map_string)
		free(s()->map_string);
	if (s() && s()->map)
		free_array(s()->map);
	if (s() && s()->file_fd)
		close(s()->file_fd);
	while (i != NBR_TXTR)
		free(s()->txtr[i++]);
	if (s() && s()->hero)
		free(s()->hero);
	free(s());
	if (vars && vars->img && vars->mlx)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars && vars->mlx_win && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->mlx_win);
	if (vars && vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars && vars->mlx)
		free(vars->mlx);
	free(vars);
	exit(0);
}

//Exécution principale de l'affichage

void	exec(struct s_so_long *so_long, t_vars *vars)
{
	int		x;
	int		y;
	int		endian;
	int		bpp;
	int		ll;

	endian = 0;
	bpp = 0;
	ll = 0;
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, so_long->map_x * 48,
			so_long->map_y * 48, "so_long");
	vars->img = mlx_new_image(vars->mlx, so_long->map_x * 48,
			so_long->map_y * 48);
	vars->addr = mlx_get_data_addr(vars->img, &bpp,
			&ll, &endian);
	mlx_key_hook(vars->mlx_win, key_hook, vars);
	mlx_hook(vars->mlx_win, 17, 0, demallocage, vars);
	mlx_loop_hook(vars->mlx, display_map, vars);
	mlx_loop(vars->mlx);
}

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
		printf("Error :\nIncorrect (amount of) char found in map\n");
	else
	{
		printf("%s\n", so_long->map_string);
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
			so_long->hero = malloc(sizeof(t_hero));
			if (!so_long->hero)
				return (0);
			i = filler(so_long, argv, vars);
			map_wiring(so_long, i, vars);
			demallocage(vars);
		}
		else
			printf("Error :\nWrong file type!\n");
	}
	else
		printf("Error :\nArgument number incorrect!\n");
	return (0);
}
