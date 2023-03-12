/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:52:05 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/12 17:48:18 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "unistd.h"
#include "../src/libft/libft.h"

typedef struct s_info
{
	char	*id;
	char	*content;
}	t_info;

typedef struct s_cub3d
{
	char	**full_file;
	t_info	*info;
	char	**map;
	int		info_size;
}	t_cub3d;


void	ft_error(char *s);
t_info	*get_infos(t_cub3d *cub);
int		check_empty(char *line);
char	**get_full_file(char *file);
int		check_end_infos(char *line);
char	**get_map(t_cub3d cub);
char	*strjoin_small(char *s1, char c);
int		check_map(char **map);

#endif