/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:38:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/01 15:38:30 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	my_mlx_put_pixel(t_my_mlx *data, int y, int x, int color)
{
	char	*dst;

	dst = data->pixel_data + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	new_main_img(t_cub3d *cub, t_my_mlx *data, int width, int heigth)
{
	int			y;
	int			x;

	data->img = mlx_new_image(cub->mlx.mlxPtr,
		width, heigth);
	data->pixel_data = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
		&(data->size_line), &(data->endian));
}

void	new_img(t_my_mlx *data, int y_pos, int x_pos, int color, int hiegth, int width)
{
	int			y;
	int			x;

	y = y_pos;
	while (y < y_pos + hiegth)
	{
		x = x_pos;
		while (x < x_pos + width)
		{
			my_mlx_put_pixel(data, y, x, color);
			x++;
		}
		y++;
	}
}


void	draw_floor_sky(t_cub3d *cub)
{
	float	y;
	float	x;

	y = -1;
	while (++y < WINDOW_HEIGTH)
	{
		x = -1;
		while (y < WINDOW_HEIGTH / 2 && ++x < WINDOW_WIDTH)
			my_mlx_put_pixel(&cub->map_img, y, x, 0x000099ff);
		while (y > WINDOW_HEIGTH / 2 && ++x < WINDOW_WIDTH)
			my_mlx_put_pixel(&cub->map_img, y, x, 0x00669999);
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
	new_img(&cub->map_img, 0, 0, 0x00000000, WINDOW_HEIGTH, WINDOW_WIDTH);
	// new_img(&cub->img, 0, 0, 0x00000000, cub->window_heigth,
			// cub->window_width);
	draw_floor_sky(cub);
	// while (cub->map[++y])
	// {
	// 	x = -1;
	// 	x_pos = 0;
	// 	while (cub->map[y][++x])
	// 	{
	// 		if (cub->map[y][x] == '1')
	// 			new_img(&cub->img, y_pos, x_pos, WALL_COLOR, floor(TILE_SIZE * SCALE_SIZE),
	// 				floor(TILE_SIZE * SCALE_SIZE));
	// 		else
	// 			new_img(&cub->img, y_pos, x_pos, FLOOR_COLOR, floor(TILE_SIZE * SCALE_SIZE),
	// 				floor(TILE_SIZE * SCALE_SIZE));
	// 		x_pos += floor(TILE_SIZE * SCALE_SIZE) + 1;
	// 	}
	// 	y_pos += floor((TILE_SIZE) * SCALE_SIZE) + 1;
	// }
	draw_player(cub, cub->player.y, cub->player.x, PLAYER_COLOR);
	mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win, cub->map_img.img, 0, 0);
	// mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win, cub->img.img, 0, 0);
	return (1);
}
