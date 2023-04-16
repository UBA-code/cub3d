/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:38:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/16 17:53:35 by ybel-hac         ###   ########.fr       */
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
	while (cub->map[++y])
	{
		x = -1;
		x_pos = 0;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'S')
			{
				cub->player.x = x_pos;
				cub->player.y = y_pos;
				return ;
			}
			x_pos += TILE_SIZE;
		}
		y_pos += TILE_SIZE;
	}
}

void	my_mlx_put_pixel(t_my_mlx *data, int y, int x, int color)
{
	char	*dst;

	dst = data->pixel_data + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	new_img(t_cub3d *cub, t_my_mlx *data, int color, int size)
{
	int			y;
	int			x;

	data->img = mlx_new_image(cub->mlx.mlxPtr, size, size);
	data->pixel_data = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
		&(data->size_line), &(data->endian));
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			my_mlx_put_pixel(data, y, x, color);
			x++;
		}
		y++;
	}
	y = -1;
}

void	draw_player(t_cub3d *cub, int y_pos, int x_pos, int color)
{
	cub->player.x = x_pos;
	cub->player.y = y_pos;
	mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win, cub->p_img.img,
		cub->player.x + TILE_SIZE / 3, cub->player.y + TILE_SIZE / 3);
}

int	render_2dmap(t_cub3d *cub)
{
	int	y;
	int	y_pos;
	int	x;
	int	x_pos;

	y = -1;
	y_pos = 0;
	// mlx_clear_window(cub->mlx.mlxPtr, cub->mlx.win);   // ! check
	while (cub->map[++y])
	{
		x = -1;
		x_pos = 0;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
				mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win,
					cub->w_img.img, x_pos, y_pos);
			else
				mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win,
					cub->f_img.img, x_pos, y_pos);
			x_pos += TILE_SIZE + 1;
		}
		y_pos += TILE_SIZE + 1;
	}
	draw_player(cub, cub->player.y, cub->player.x, PLAYER_COLOR);
	return (1);
}
