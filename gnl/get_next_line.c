/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 09:03:23 by rdel-agu          #+#    #+#             */
/*   Updated: 2021/12/09 16:01:47 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	isendline(char *r)
{
	int	j;

	j = 0;
	if (!r)
		return (0);
	while (r[j])
	{
		if (r[j] == '\n')
			return (1);
		j++;
	}
	return (0);
}

int	isnewline(char *s)
{
	if (s[0] == '\n')
		return (1);
	return (0);
}

char	*second_r(char *r)
{
	char	*second_r;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (r == NULL)
		return (NULL);
	while (r[i] && r[i] != '\n')
		i++;
	if (r[i] == '\0')
		return (demallocage_gnl(r));
	i += isnewline(&r[i]);
	second_r = (char *)malloc(sizeof(char) * (ft_strlen(r) - i + 1));
	if (!second_r)
		return (NULL);
	while (r[i])
		second_r[j++] = r[i++];
	second_r[j] = '\0';
	free(r);
	r = NULL;
	return (second_r);
}

char	*rcopyline(char *r)
{
	int		i;
	char	*returnstr;

	i = 0;
	if (!(r) || !r[0])
		return (NULL);
	while (r[i] != '\0' && r[i] != '\n')
		i++;
	i += isnewline(&r[i]);
	returnstr = (char *) malloc(sizeof(char) * (i + 1));
	if (!returnstr)
		return (NULL);
	i = 0;
	while (r[i] != '\0' && r[i] != '\n')
	{
		returnstr[i] = r[i];
		i++;
	}
	if (r[i] == '\n')
	{
		returnstr[i] = r[i];
		i++;
	}
	returnstr[i] = '\0';
	return (returnstr);
}

char	*get_next_line(int fd)
{	
	static char	*r[1024];
	char		*buffer;
	int			i;
	char		*tmp;

	i = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while ((isendline(r[fd]) == 0) && (i != 0))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (demallocage_gnl(buffer));
		buffer[i] = '\0';
		r[fd] = ft_strjoin(r[fd], buffer);
	}
	free(buffer);
	tmp = rcopyline(r[fd]);
	r[fd] = second_r(r[fd]);
	return (tmp);
}
