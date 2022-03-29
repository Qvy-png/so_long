/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:36:22 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/03/23 13:36:24 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//Permet de simplifier keyhook, ainsi que de ne pas compter quand on avance dans
//un mur
//renvoie un int

int	key_hook_simplifyer(char hero, char c, int i)
{
	if (c == '-')
	{
		if (hero == 'y')
		{
			s()->hero->y -= 48;
		}
		if (hero == 'x')
			s()->hero->x -= 48;
	}
	if (c == '+')
	{
		if (hero == 'y')
			s()->hero->y += 48;
		if (hero == 'x')
			s()->hero->x += 48;
	}
	i++;
	ft_printf("Vous avez fait %d pas!\n", i);
	return (i);
}

//Permet d'enregistrer les appuis de touches
//renvoie un int

int	key_hook(int keycode, t_vars *vars)
{
	static int		step = 0;

	if (keycode == 119)
		if (s()->hero->y > 48
			&& s()->map[(s()->hero->y / 48) - 1][s()->hero->x / 48] != '1')
			step = key_hook_simplifyer('y', '-', s()->steps);
	if (keycode == 97)
		if (s()->hero->x > 48
			&& s()->map[(s()->hero->y / 48)][s()->hero->x / 48 - 1] != '1')
			step = key_hook_simplifyer('x', '-', s()->steps);
	if (keycode == 115)
		if (s()->hero->y < (s()->map_y * 48) - 96
			&& s()->map[(s()->hero->y / 48) + 1][s()->hero->x / 48] != '1')
			step = key_hook_simplifyer('y', '+', s()->steps);
	if (keycode == 100)
		if (s()->hero->x < (s()->map_x * 48) - 96
			&& s()->map[(s()->hero->y / 48)][s()->hero->x / 48 + 1] != '1')
			step = key_hook_simplifyer('x', '+', s()->steps);
	if (keycode == 65307)
		demallocage(vars);
	s()->steps = step;
	return (0);
}
