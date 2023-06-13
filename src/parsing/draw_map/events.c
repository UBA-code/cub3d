/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:57:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/06/13 17:50:41 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	key_pressed(int keycode, t_cub3d *cub)
{
	if (keycode == UP || keycode == UP_ARROW)
		cub->player.walk = -1;
	else if (keycode == DOWN || keycode == DOWN_ARROW)
		cub->player.walk = 1;
	else if (keycode == RIGHT)
		cub->player.turn = 1;
	else if (keycode == LEFT)
		cub->player.turn = -1;
	else if (keycode == LEFT_ARROW)
		cub->player.rotate = -TURN_SPEED;
	else if (keycode == RIGHT_ARROW)
		cub->player.rotate = TURN_SPEED;
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win);
		ft_exit(cub, 0);
	}
	return (1);
}

int	key_released(int keycode, t_cub3d *cub)
{
	if (keycode == UP || keycode == UP_ARROW)
		cub->player.walk = 0;
	else if (keycode == DOWN || keycode == DOWN_ARROW)
		cub->player.walk = 0;
	else if (keycode == RIGHT)
		cub->player.turn = 0;
	else if (keycode == LEFT)
		cub->player.turn = 0;
	else if (keycode == LEFT_ARROW)
		cub->player.rotate = 0;
	else if (keycode == RIGHT_ARROW)
		cub->player.rotate = 0;
	return (1);
}

int	mouse_move(int x, int y, t_cub3d *cub)
{
	if ((y <= WINDOW_HEIGTH && y >= 0) && (x <= WINDOW_WIDTH && x >= 0))
	{
		if (x > WINDOW_WIDTH / 2 && x < WINDOW_WIDTH)
			cub->player.angel += TURN_SPEED;
		else if (x <= WINDOW_WIDTH / 2 && x > 0)
			cub->player.angel -= TURN_SPEED;
	}
	return (1);
}
