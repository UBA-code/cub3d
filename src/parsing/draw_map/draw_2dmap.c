/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2dmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:11:40 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/16 23:44:02 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	move_player(int keycode, void *cub_ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)cub_ptr;
	if (keycode == UP)
		cub->player.y -= 5;
	else if (keycode == DOWN)
		cub->player.y += 5;
	else if (keycode == RIGHT)
		cub->player.x += 5;
	else if (keycode == LEFT)
		cub->player.x -= 5;
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx.mlxPtr, cub->mlx.win);
		ft_exit(cub, 0);
	}
	render_2dmap(cub);
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
	cub->mlx.mlxPtr = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlxPtr, cub->map_width * TILE_SIZE + cub->map_width,
		cub->map_height * TILE_SIZE + cub->map_height, "juex hh");
	new_img(cub, &cub->p_img, PLAYER_COLOR, TILE_SIZE / 2);
	new_img(cub, &cub->f_img, FLOOR_COLOR, TILE_SIZE);
	new_img(cub, &cub->w_img, WALL_COLOR, TILE_SIZE);
	init_player(cub);
	render_2dmap(cub);
	mlx_hook(cub->mlx.win, 2, 1L << 0, move_player, cub); // 1L << 0 = keypress mask
	mlx_loop(cub->mlx.mlxPtr);
}
