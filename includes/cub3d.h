/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:52:05 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/16 18:14:53 by ybel-hac         ###   ########.fr       */
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
// # include "mlx_int.h"


#define WALL_COLOR 0x00ffffff
#define FLOOR_COLOR 0x0000ffff
#define PLAYER_COLOR 0x00ff0000
#define TILE_SIZE	32
#define PI			3.141592653589793238
#define UP		119
#define DOWN	115
#define RIGHT	100
#define LEFT	97
#define	ESC		65307
#define RIGHT_ARROW	65363
#define LEFT_ARROW	65361

typedef struct s_info
{
	char	*id;
	char	*content;
}	t_info;

typedef struct s_mlx
{
	void*	mlxPtr;
	void*	win;
} t_mlx;

typedef struct s_my_mlx
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*pixel_data;
	void	*img;
} t_my_mlx;

typedef struct s_player
{
	float		y;
	float		x;
	float		dirX;
	float		dirY;
}	t_player;

typedef struct s_cub3d
{
	t_my_mlx	p_img;		
	t_my_mlx	w_img;		
	t_my_mlx	f_img;		
	char		**full_file;
	t_info		*info;
	char		**map;
	int			info_size;
	int			map_height;
	int			map_width;
	t_mlx		mlx;
	t_player	player;
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
int		check_characters(char **map);
void	copy_map(char **dst, char *src, int len);
char	get_player(char **map);
void	move_back(char *c1, char *c2, char player);
void	check_info(t_cub3d cub);
void	check_colors(t_cub3d *cub);
void	free_utils(t_cub3d cub);
void	ft_exit(t_cub3d *cub, int error);



// ?  draw

void	draw_2dmap(t_cub3d *cub);
int	render_2dmap(t_cub3d *cub);
void	draw_player(t_cub3d *cub, int y_pos, int x_pos, int color);
void	my_mlx_put_pixel(t_my_mlx *data, int y, int x, int color);
void	new_img(t_cub3d *cub, t_my_mlx *data, int color, int size);
void	init_player(t_cub3d *cub);



#endif
