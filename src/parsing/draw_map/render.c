/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:38:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/12 12:01:48 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	my_mlx_put_pixel(t_my_mlx *data, int y, int x, int color)
{
	char	*dst;

	dst = data->pixel_data
		+ (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void	draw_minimap(t_cub3d *cub)
{
	int		y;
	t_obj	img;
	int		x;

	y = -1;
	img.y_pos = 0;
	new_obj_img(&cub->img, cub->window_height, cub->window_width);
	while (cub->map[++y])
	{
		x = -1;
		img.x_pos = 0;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
				new_img(&cub->img, img, WALL_COLOR,
					floor(TILE_SIZE * SCALE_SIZE));
			else
				new_img(&cub->img, img, FLOOR_COLOR,
					floor(TILE_SIZE * SCALE_SIZE));
			img.x_pos += floor(TILE_SIZE * SCALE_SIZE);
		}
		img.y_pos += floor((TILE_SIZE) * SCALE_SIZE);
	}
	draw_player(cub, cub->player.y, cub->player.x, PLAYER_COLOR);
}

int	render_2dmap(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.mlxPtr, cub->mlx.win);
	new_obj_img(&cub->map_img, WINDOW_HEIGTH, WINDOW_WIDTH);
	cub->player.angel += cub->player.rotate;
	move_player(cub, cub->player.turn, cub->player.walk, 'c');
	draw_floor_sky(cub);
	draw_minimap(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx.mlxPtr,
		cub->mlx.win, cub->map_img.img, 0, 0);
	mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win, cub->img.img, 0, 0);
	return (1);
}