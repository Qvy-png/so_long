/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_scan_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:38:33 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/02/17 15:10:58 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Récupère la taille de la map pour pouvoir récupérer le fichier en une string

void	map_size(struct s_so_long *so_long)
{
	int		i;
	int		fd;
	int		reader;
	char	buffer[1];

	i = 0;
	reader = 1;
	fd = open(so_long->file_name, O_RDWR);
	if (fd != -1)
	{
		while (reader != 0)
		{
			reader = read(fd, buffer, 1);
			i++;
		}
		close(fd);
	}
	so_long->map_size = i;
}

// Récupère le fichier en une string proprement allouée

void	map_to_str(char *str, struct s_so_long *so_long)
{
	int		ret;
	int		status;
	char	*file;
	int		i;

	ret = 0;
	i = so_long->map_size;
	file = (char *)malloc(sizeof(char) * i + 1);
	if (!file)
		return ;
	status = open(str, O_RDWR);
	if (status != -1)
	{
		ret = read(status, file, i);
		close(status);
	}
	file[ret] = 0;
	so_long->map_but_its_a_string_actually = ft_strdup(file);
	free(file);
}

// Regarde dans une string si les charactères obligatoires de la map, 
// sont présents dans la chaine de charactères passée en paramètre
// renvoie un int

int	is_supposed_to_be_in_map(struct s_so_long *so_long)
{
	int	i;

	i = 0;
	while (so_long->map_but_its_a_string_actually[i])
	{
		if (so_long->map_but_its_a_string_actually[i] != '1'
			&& so_long->map_but_its_a_string_actually[i] != '0'
			&& so_long->map_but_its_a_string_actually[i] != 'C'
			&& so_long->map_but_its_a_string_actually[i] != 'P'
			&& so_long->map_but_its_a_string_actually[i] != 'E'
			&& so_long->map_but_its_a_string_actually[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// Regarde dans une string passée en paramètres si le dernier
// char est un 1 ou non
// renvoie un int

int	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '1')
		return (1);
	else
		return (0);
}

// Regarde dans une string passée en paramètres si le premier
// char est un 1 ou non
// renvoie un int

int	first_char(char *str)
{
	if (str[0] == '1')
		return (1);
	else
		return (0);
}
