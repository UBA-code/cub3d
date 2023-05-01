/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:52:05 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/01 15:37:20 by ybel-hac         ###   ########.fr       */
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


#define LINE_COLOR 0x00ff0000
#define LINE_GREEN_COLOR 0x0000ff00
#define WALL_COLOR 0x00ffffff
#define FLOOR_COLOR 0x0000ffff
#define PLAYER_COLOR 0x00ff0000
#define TILE_SIZE	100
#define SCALE_SIZE 0.07
#define PI			3.141592653589793238
#define turn_SPEED_UP		65365
#define turn_SPEED_DOWN		65366
#define UP		13
#define DOWN	1
#define RIGHT	2
#define LEFT	0
#define	ESC		53
#define RIGHT_ARROW	124
#define LEFT_ARROW	123
#define PLAYER_SPEED	30.0
#define TURN_SPEED		10.0
#define ONE_DEGRESS 0.0174533
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGTH 720
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
	float		difX;
	float		difY;
	float		steps;
	float		x_inc;
	float		y_inc;
	float		angel;
	float		turn_speed;
	float		walk_speed;
	int			turn;
	int			walk;
}	t_player;

typedef struct s_cub3d
{
	t_my_mlx	img;
	t_my_mlx	map_img;
	char		**full_file;
	t_info		*info;
	char		**map;
	int			info_size;
	int			map_height;
	int			map_width;
	int			window_heigth;
	int			window_width;
	t_mlx		mlx;
	t_mlx		map_mlx;
	t_player	player;
	char		p;
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
int		check_characters(t_cub3d *cub, char **map);
void	copy_map(char **dst, char *src, int len);
char	get_player(char **map);
void	move_back(char *c1, char *c2, char player);
void	check_info(t_cub3d cub);
void	check_colors(t_cub3d *cub);
void	free_utils(t_cub3d cub);
void	ft_exit(t_cub3d *cub, int error);
int		my_abs(int x);



// ?  draw

void	draw_2dmap(t_cub3d *cub);
int		render_2dmap(t_cub3d *cub);
void	my_mlx_put_pixel(t_my_mlx *data, int y, int x, int color);
void	new_main_img(t_cub3d *cub, t_my_mlx *data, int width, int heigth);
void	new_img(t_my_mlx *data, int y_pos, int x_pos,
			int color, int hiegth, int width);
void	init_player(t_cub3d *cub);
int		check_wall(t_cub3d *cub, float new_x, float new_y);
int		move_check(int keycode, void *cub_ptr);

// player
void	init_player(t_cub3d *cub);
void	draw_line(t_cub3d *cub);
void	draw_player(t_cub3d *cub, float y_pos, float x_pos, int color);

#endif
