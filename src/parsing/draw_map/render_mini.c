/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:38:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/19 00:31:07 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	my_mlx_put_pixel(t_my_mlx *data, int y, int x, int color)
{
	char	*dst;

	dst = data->pixel_data + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	new_main_img(t_cub3d *cub, t_my_mlx *data)
{
	int			y;
	int			x;

	data->img = mlx_new_image(cub->mlx.mlxPtr,
		cub->window_width, cub->window_heigth);
	data->pixel_data = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
		&(data->size_line), &(data->endian));
}

void	new_img(t_cub3d *cub, int y_pos, int x_pos, int color, int hiegth, int width)
{
	int			y;
	int			x;

	y = y_pos;
	while (y < y_pos + hiegth)
	{
		x = x_pos;
		while (x < x_pos + width)
		{
			my_mlx_put_pixel(&cub->img, y, x, color);
			x++;
		}
		y++;
	}
}

int	render_2dmap(t_cub3d *cub)
{
	int	y;
	int	y_pos;
	int	x;
	int	x_pos;

	y = -1;
	y_pos = 0;
	mlx_clear_window(cub->mlx.mlxPtr, cub->mlx.win);   // ! check
	new_img(cub, 0, 0, 0x00000000, cub->window_heigth, cub->window_width);
	while (cub->map[++y])
	{
		x = -1;
		x_pos = 0;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
				new_img(cub, y_pos, x_pos, WALL_COLOR, TILE_SIZE * SCALE_SIZE,
					TILE_SIZE * SCALE_SIZE);
			else
				new_img(cub, y_pos, x_pos, FLOOR_COLOR, TILE_SIZE * SCALE_SIZE,
					TILE_SIZE * SCALE_SIZE);
			x_pos += TILE_SIZE * SCALE_SIZE + 1;
		}
		y_pos += TILE_SIZE * SCALE_SIZE + 1;
	}
	draw_player(cub, cub->player.y, cub->player.x, PLAYER_COLOR);
	mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win, cub->img.img, 0, 0);
	return (1);
}
