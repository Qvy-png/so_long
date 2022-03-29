/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:10:29 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/02/11 11:10:31 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Copie une string en faisant une allocation propre 
// retourne une chaine de char

char	*ft_strdup(char *src)
{
	int		i;
	char	*dup;

	i = -1;
	dup = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dup)
		return (NULL);
	while (src[++i])
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}

// Vérifie si le fichier est un .ber ou non
// retourne un int

int	is_dot_ber(char *name, char *extention)
{
	int	i;
	int	j;

	i = ft_strlen(name);
	j = ft_strlen(extention);
	if (name[0] == '.' || name[i - 5] == '/')
		return (0);
	while (j >= 0)
	{
		if (extention[j] == name[i])
		{
			i--;
			j--;
		}
		else
			return (0);
	}
	return (1);
}

void	record_hero(struct s_so_long *so_long)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < so_long->map_y)
	{
		while (x < so_long->map_x)
		{
			if (so_long->map[y][x] == 'P')
			{
				so_long->map[y][x] = '0';
				so_long->hero->y = y * 48;
				so_long->hero->x = x * 48;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

// Free un tableau en 2D

void	free_array(char **twoD)
{
	int	i;

	i = 0;
	while (twoD && twoD[i] != NULL)
	{
		free(twoD[i]);
		i++;
	}
	if (twoD)
		free(twoD);
}

int	cnt_collect(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 'C')
			j++;
		i++;
	}
	return (j);
}
