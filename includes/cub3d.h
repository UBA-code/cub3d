/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:52:05 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/13 15:58:26 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "math.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"
# include "unistd.h"
# include "../src/libft/libft.h"
# include "mlx.h"
# include "mlx_int.h"


#define TILE_SIZE 32
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
	int		map_height;
	int		map_width;
}	t_cub3d;

void	ft_error(char *s);
t_info	*get_infos(t_cub3d *cub);
int		check_empty(char *line, char c);
char	**get_full_file(char *file);
int		check_end_infos(char *line);
char	**get_map(t_cub3d *cub);
char	*strjoin_small(char *s1, char c);
int		check_map(char **map, t_cub3d *cub);
char	**dup_tab(char **map);
int		get_tab_len(char **tab);
void	tab_free(char **tab);
void	ft_swap(char *c1, char *c2);
void	move_player(char *c1, char *c2, char player);
int		check_characters(char **map);
void	copy_map(char **dst, char *src, int len);
char	get_player(char **map);
void	move_back(char *c1, char *c2, char player);
void	check_info(t_cub3d cub);
void	check_colors(t_cub3d *cub);
void	free_utils(t_cub3d cub);

#endif