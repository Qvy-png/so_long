/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:23:11 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/02/08 15:23:13 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "mlx.h"

struct s_so_long
{
	char	*file_name;
	int		file_fd;
	int		map_size;
	int		map_x;
	int		map_y;
	char	*map_but_its_a_string_actually;
	char	**map;
	int		is_rectangle;
};

int		last_char(char *str);
int 	first_char(char *str);
int		map_filler(struct s_so_long *so_long);
int		map_width(struct s_so_long *so_long);
int		map_height(struct s_so_long *so_long);
int		is_dot_ber(char *name, char *extention);
int		is_supposed_to_be_in_map(struct s_so_long *so_long);
int		filler(struct s_so_long *so_long, char **argv);

char	*ft_strdup(char *src);

void	map_wiring(int i);
void	free_array(char **twoD);
void	map_size(struct s_so_long *so_long);
void	map_alloc(struct s_so_long *so_long);
void	demallocage(struct s_so_long *so_long);
void	map_tab_filler(struct s_so_long *so_long);
void	map_to_str(char *str, struct s_so_long *so_long);

#endif
