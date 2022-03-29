/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:23:01 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/02/08 15:23:02 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Parcours la première ligne du fichier pour avoir la taille en largeur de map
// renvoie un int

int	map_width(struct s_so_long *so_long)
{
	int	i;

	i = 0;
	while (so_long->map_string[i])
	{
		if (so_long->map_string[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// Vérifie si une string contient un '\n'

int	no_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

// ft_strlen mais sa condition de fin inclue \n

int	custom_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

// Récupère la hauteur de la map en utilisant no_new_line, 
// pour capter la fin du fichier en utilisant get_next_line
// renvoie un int

int	map_height(struct s_so_long *so_long)
{
	int		i;
	int		j;
	char	*tmp;
	int		verif;

	i = 0;
	j = 0;
	so_long->is_rectangle = 1;
	while (j == 0)
	{
		tmp = get_next_line(so_long->file_fd);
		j = no_new_line(tmp);
		verif = custom_strlen(tmp);
		if (verif != so_long->map_x)
			so_long->is_rectangle = 0;
		i++;
		free(tmp);
	}
	return (i);
}
