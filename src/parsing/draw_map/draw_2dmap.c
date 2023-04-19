/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2dmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:11:40 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/19 00:37:57 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"


int	check_wall(t_cub3d *cub, int new_x, int new_y)
{
	int	x;
	int	x_check;
	int	y;

	x = floor((new_x) / (TILE_SIZE * SCALE_SIZE + 1));
	x_check = floor((new_x + 1) / (TILE_SIZE * SCALE_SIZE + 1));
	y = floor((new_y) / (TILE_SIZE * SCALE_SIZE + 1));
	if (cub->map[y][x] == '1' || cub->map[y][x_check] == '1')
		return (1);
	return (0);
}

void	move_player(t_cub3d *cub, int x, int y, char c)
{
	int	temp;

	temp = 0;
	if (c == 'u')
	{
		while (!check_wall(cub, x, --y) && temp++ < PLAYER_SPEED)
			cub->player.y = y;
		cub->player.x = x;
	}
	else if (c == 'd')
	{
		while (!check_wall(cub, x, ++y) && temp++ < PLAYER_SPEED)
			cub->player.y = y;
		cub->player.x = x;
	}
	else if (c == 'r')
	{
		while (!check_wall(cub, ++x, y) && temp++ < PLAYER_SPEED)
			cub->player.x = x;
		cub->player.y = y;
	}
	else if (c == 'l')
	{
		while (!check_wall(cub, --x, y) && temp++ < PLAYER_SPEED)
			cub->player.x = x;
		cub->player.y = y;
	}
}

int	move_check(int keycode, void *cub_ptr)
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
		cub->player.angel -= TURN_SPEED;
	else if (keycode == RIGHT_ARROW)
		cub->player.angel += TURN_SPEED;
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx.mlxPtr, cub->mlx.win);
		ft_exit(cub, 0);
	}
	// render_2dmap(cub);
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
	cub->window_heigth = cub->map_height * (TILE_SIZE + 1);
	cub->window_width = cub->map_width * (TILE_SIZE + 1);
	cub->mlx.mlxPtr = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlxPtr, cub->window_width,
		cub->window_heigth, "juex hh");
	// new_img(cub, &cub->p_img, PLAYER_COLOR, TILE_SIZE / 2);
	// new_img(cub, &cub->f_img, FLOOR_COLOR, TILE_SIZE);
	// new_img(cub, &cub->w_img, WALL_COLOR, TILE_SIZE);
	init_player(cub);
	new_main_img(cub, &cub->img);
	// render_2dmap(cub);
	mlx_hook(cub->mlx.win, 2, 1L << 0, move_check, cub); // 1L << 0 = keypress mask
	mlx_loop_hook(cub->mlx.mlxPtr, render_2dmap, cub);
	mlx_loop(cub->mlx.mlxPtr);
}
