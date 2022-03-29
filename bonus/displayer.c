/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:36:35 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/03/23 13:36:36 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//Permet d'afficher une texture

void	display_stuff(t_vars *vars, char *str, int x, int y)
{
	int		width;
	int		height;

	width = 0;
	height = 0;
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_xpm_file_to_image(vars->mlx, str, &width, &height);
	if (vars->img == NULL)
	{
		ft_printf("xmp lecture has failed\n");
		demallocage(vars);
		exit(0);
	}
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img,
		x * 48, y * 48);
}

//Permet de simplifier la foncion secondaire de display_map

void	display_simplifyer(t_vars *vars, char c, char *str)
{
	if (s()->map[s()->y][s()->x] == c)
		display_stuff(vars, str, s()->x, s()->y);
}

//Fonction secondaire de display_map

void	display_map_sec(t_vars *vars)
{
	while (s()->x < s()->map_x)
	{
		display_simplifyer(vars, WALL, s()->txtr[WALL_TXTR]);
		display_simplifyer(vars, FLOOR, s()->txtr[FLOOR_TXTR]);
		display_simplifyer(vars, COLLECTIBLE, s()->txtr[COLLECTIBLE_TXTR]);
		display_simplifyer(vars, EXIT, s()->txtr[EXIT_TXTR]);
		display_stuff(vars, s()->txtr[HERO_TXTR], (s()->hero->x / 48),
			(s()->hero->y / 48));
		s()->x++;
	}
	s()->x = 0;
	s()->y++;
}

//Affiche la map de base
//Renvoie un int

int	display_map(t_vars *vars)
{
	char	*str;

	str = ft_itoa(s()->steps);
	s()->x = 0;
	s()->y = 0;
	while (s()->y < s()->map_y)
	{	
		mlx_string_put(vars->mlx, vars->mlx_win, 20, 20, 0x0ffffff, str);
		display_map_sec(vars);
	}
	free(str);
	if (s()->collect_num <= 0
		&& s()->map[s()->hero->y / 48][s()->hero->x / 48] == EXIT)
	{
		ft_printf("Bien joué, vous avez gagné!!\n");
		demallocage(vars);
	}
	if (s()->map[s()->hero->y / 48][s()->hero->x / 48] == COLLECTIBLE)
	{
		s()->map[s()->hero->y / 48][s()->hero->x / 48] = FLOOR;
		s()->collect_num = s()->collect_num - 1;
	}
	return (0);
}
