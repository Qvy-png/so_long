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
	if (name[0] == '.' || name[i - 5] == '/') ///////////////////AAAAAAAAAAA FAIRE LES CONDITIONS CHELOUS POUR LE .BER
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
