/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:38:16 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/02/17 13:38:18 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Alloue la base du tableau en 2D selon la hauteur de la map

void	map_alloc(struct s_so_long *so_long)
{
	so_long->map = (char **)malloc(sizeof(char *) * (so_long->map_y + 1));
	so_long->map[so_long->map_y] = NULL;
	if (so_long->map == NULL)
		return ;
}

// Regarde si une string n'est uniquement composée de 1 ou non
// renvoie un int

int	is_ones(struct s_so_long *so_long, char *str)
{
	int	i;

	i = 0;
	while (i < so_long->map_x)
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

// Regarde si le premier et avant dernier char de la string est un 1
// renvoie un int

int	is_sides_and_mid(struct s_so_long *so_long, char *str)
{
	if (str[0] == '1' && str[so_long->map_x - 1] == '1')
		return (1);
	return (0);
}

// Utilise is_ones et is_sides_and_mid pour vérifier la conformité de la map
// renvoie un int

int	map_true_verif(struct s_so_long *so_long, char *str, int i)
{
	if (i == 0 || i == so_long->map_y -1)
		if (is_ones(so_long, str) == 0)
			return (-1);
	if (i >= 1 && i < so_long->map_y - 1)
		if (is_sides_and_mid(so_long, str) == 0)
			return (-2);
	return (1);
}

// Remplie le tableau en 2D avec le fichier passé en paramètres
// renvoie un int

int	map_filler(struct s_so_long *so_long)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < so_long->map_y)
	{
		so_long->map[i] = get_next_line(so_long->file_fd);
		j = map_true_verif(so_long, so_long->map[i], i);
		if (j != 1)
			return (j);
		i++;
	}
	return (1);
}
