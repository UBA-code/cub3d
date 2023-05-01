/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2dmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:11:40 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/01 20:37:00 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_wall(t_cub3d *cub, float new_x, float new_y)
{
	int	x;
	int	x_check;
	int	y;

	x = floor((new_x) / floor(TILE_SIZE + 1 / SCALE_SIZE));
	x_check = floor((new_x + 1) / floor(TILE_SIZE + 1 / SCALE_SIZE));
	y = floor((new_y) / floor(TILE_SIZE + 1 / SCALE_SIZE));
	if (cub->map[y][x] == '1' || cub->map[y][x_check] == '1')
		return (1);
	return (0);
}

void	move_player_angel(t_cub3d *cub, float angel, float y_sin, float x_cos)
{
	float	y;
	float	x;
	int		loop;

	y_sin = sin(angel * (PI / 180.0));
	x_cos = cos(angel * (PI / 180.0));
	y = cub->player.y;
	x = cub->player.x;
	loop = 0;
	while (!check_wall(cub, x - (loop * x_cos), y - (loop * y_sin)) && loop < PLAYER_SPEED)
		loop++;
	if (!check_wall(cub, x, y))
		loop--;
	cub->player.x -= loop * x_cos;
	cub->player.y -= loop * y_sin;
}

void	move_player(t_cub3d *cub, float x, float y, char c)
{
	int	temp;

	temp = -1;
	if (y == -1)
		move_player_angel(cub, cub->player.angel, 0, 0);
	if (y == 1)
		move_player_angel(cub, cub->player.angel + 180.0, 0, 0);
	if (x == 1)
		move_player_angel(cub, cub->player.angel + 90.0, 0, 0);
	if (x == -1)	
		move_player_angel(cub, cub->player.angel - 90.0, 0, 0);
}

int	key_check(int keycode, void *cub_ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)cub_ptr;
	if (keycode == UP)
		move_player(cub, cub->player.x, cub->player.y, 'u');
	else if (keycode == DOWN)
		move_player(cub, cub->player.x, cub->player.y, 'd');
	else if (keycode == RIGHT)
		move_player(cub, cub->player.x, cub->player.y, 'r');
	else if (keycode == LEFT)
		move_player(cub, cub->player.x, cub->player.y, 'l');
	else if (keycode == LEFT_ARROW)
		cub->player.angel -= cub->player.turn_speed;
	else if (keycode == RIGHT_ARROW)
		cub->player.angel += cub->player.turn_speed;
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx.mlxPtr, cub->mlx.win);
		ft_exit(cub, 0);
	}
	else if (keycode == turn_SPEED_UP)
		cub->player.turn_speed++;
	else if (keycode == turn_SPEED_DOWN)
		cub->player.turn_speed--;
	if (cub->player.turn_speed < 0)
		cub->player.turn_speed = 3;
	return (1);
}

int key_pressed(int keycode, t_cub3d *cub)
{
	if (keycode == UP)
		cub->player.walk = -1;
	else if (keycode == DOWN)
		cub->player.walk = 1;
	else if (keycode == RIGHT)
		cub->player.turn = 1;
	else if (keycode == LEFT)
		cub->player.turn = -1;
	else if (keycode == LEFT_ARROW)
		cub->player.rotate = -1;
	else if (keycode == RIGHT_ARROW)
		cub->player.rotate = 1;
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx.mlxPtr, cub->mlx.win);
		ft_exit(cub, 0);
	}
	return (1);
}

int key_released(int keycode, t_cub3d *cub)
{
	if (keycode == UP)
		cub->player.walk = 0;
	else if (keycode == DOWN)
		cub->player.walk = 0;
	else if (keycode == RIGHT)
		cub->player.turn = 0;
	else if (keycode == LEFT)
		cub->player.turn = 0;
	else if (keycode == LEFT_ARROW)
		cub->player.rotate = 0;
	else if (keycode == RIGHT_ARROW)
		cub->player.rotate = 0;
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx.mlxPtr, cub->mlx.win);
		ft_exit(cub, 0);
	}
	return (1);
}

void	draw_2dmap(t_cub3d *cub)
{
	int	y;
	int	y_pos;
	int	x;
	int	x_pos;

	y = -1;
	y_pos = 0;
	x_pos = 0;
	cub->window_heigth = cub->map_height * (TILE_SIZE * SCALE_SIZE + 1);
	cub->window_width = cub->map_width * (TILE_SIZE * SCALE_SIZE + 1);
	cub->mlx.mlxPtr = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlxPtr, WINDOW_WIDTH,
		WINDOW_HEIGTH, "juex hh");
	init_player(cub);
	new_main_img(cub, &cub->img, cub->window_width,
			cub->window_heigth);
	new_main_img(cub, &cub->map_img, WINDOW_WIDTH, WINDOW_HEIGTH);
	mlx_hook(cub->mlx.win, 2, 0L, key_pressed, cub); // 1L << 0 = keypress mask
	mlx_hook(cub->mlx.win, 3, 0L, key_released, cub); // 1L << 0 = keypress mask
	mlx_hook(cub->mlx.win, 17, 1L << 0, ft_exit, cub); // 1L << 0 = keypress mask
	mlx_loop_hook(cub->mlx.mlxPtr, render_2dmap, cub);
	mlx_loop(cub->mlx.mlxPtr);
}
