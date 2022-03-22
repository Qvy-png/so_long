#include "../includes/so_long.h"

//Permet de simplifier keyhook, ainsi que de ne pas compter quand on avance dans
//un mur
//renvoie un int

int	key_hook_simplifyer(char hero, char c, int i, t_vars *vars)
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
	printf("Vous avez fait %d pas!\n", i);
	return (i);
}

//Permet d'enregistrer les appuis de touches
//renvoie un int

int	key_hook(int keycode, t_vars *vars)
{
	char	min;
	char	pos;
	
	if (keycode == 119)
		if (s()->hero->y > 48
			&& s()->map[(s()->hero->y / 48) - 1][s()->hero->x / 48] != '1')
			s()->steps = key_hook_simplifyer('y', '-', s()->steps, vars);
	if (keycode == 97)
		if (s()->hero->x > 48
			&& s()->map[(s()->hero->y / 48)][s()->hero->x / 48 - 1] != '1')
			s()->steps = key_hook_simplifyer('x', '-', s()->steps, vars);
	if (keycode == 115)
		if (s()->hero->y < (s()->map_y * 48) - 96
			&& s()->map[(s()->hero->y / 48) + 1][s()->hero->x / 48] != '1')
			s()->steps = key_hook_simplifyer('y', '+', s()->steps, vars);
	if (keycode == 100)
		if (s()->hero->x < (s()->map_x * 48) - 96
			&& s()->map[(s()->hero->y / 48)][s()->hero->x / 48 + 1] != '1')
			s()->steps = key_hook_simplifyer('x', '+', s()->steps, vars);
	if (keycode == 65307)
		demallocage(vars);
	return (0);
}
