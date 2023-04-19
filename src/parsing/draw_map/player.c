/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:03:12 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/19 00:40:21 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_player(t_cub3d *cub)
{
	int	y;
	int	x;
	int	y_pos;
	int	x_pos;

	y_pos = 0;
	y = -1;
	cub->player.angel = ANGEL;
	while (cub->map[++y])
	{
		x = -1;
		x_pos = 0;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'S')
			{
				cub->player.x = x_pos + (TILE_SIZE * SCALE_SIZE / 2);
				cub->player.y = y_pos + (TILE_SIZE * SCALE_SIZE / 2);
				return ;
			}
			x_pos += TILE_SIZE * SCALE_SIZE + 1;
		}
		y_pos += TILE_SIZE * SCALE_SIZE + 1;
	}
}

void	draw_line(t_cub3d *cub)
{
	float	y;
	float	x;
	int		i;
	float	rad;
	float	length;
	float	angel;
	int		rays;

	length = 100000.0;
	rays = -1;
	angel = cub->player.angel - 45.0;
	while (++rays < cub->window_width)
	{
		rad = angel * PI / 180.0;
		cub->player.dirX = cub->player.x - round(length * cos(rad));
		cub->player.dirY = cub->player.y - round(length * sin(rad));
		cub->player.difX = cub->player.dirX - cub->player.x;
		cub->player.difY = cub->player.dirY - cub->player.y;
		cub->player.steps = my_abs(cub->player.difY);
		if (my_abs(cub->player.difX) > my_abs(cub->player.difY))
			cub->player.steps = my_abs(cub->player.difX);
		cub->player.x_inc = (float)cub->player.difX / (float)cub->player.steps;
		cub->player.y_inc = (float)cub->player.difY / (float)cub->player.steps;
		i = 0;
		y = cub->player.y;
		x = cub->player.x;
		i = 0;
		while (i < cub->player.steps && !check_wall(cub, round(x), round(y)))
		{
			if (floor(angel) == floor(cub->player.angel))
				my_mlx_put_pixel(&cub->img, round(y), round(x), LINE_GREEN_COLOR);
			else
				my_mlx_put_pixel(&cub->img, round(y), round(x), LINE_COLOR);
			y += cub->player.y_inc;
			x += cub->player.x_inc;
			i++;
		}
		angel += 90.0 / cub->window_width;
	}
}

void	draw_player(t_cub3d *cub, int y_pos, int x_pos, int color)
{
	cub->player.x = x_pos;
	cub->player.y = y_pos;
	new_img(cub, cub->player.y, cub->player.x ,color, SCALE_SIZE * 5,
		SCALE_SIZE * 5);
	draw_line(cub);
}