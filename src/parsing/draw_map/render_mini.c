/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:38:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/18 15:43:44 by ybel-hac         ###   ########.fr       */
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
				cub->player.x = x_pos + TILE_SIZE / 2;
				cub->player.x_old = x_pos + TILE_SIZE / 2;
				cub->player.y = y_pos + TILE_SIZE / 2;
				cub->player.y_old = y_pos + TILE_SIZE / 2;
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
	rays = 0;
	angel = cub->player.angel - 45.0;
	while (rays < cub->window_width)
	{
		rad = angel * PI / 180.0;
		cub->player.dirX = cub->player.x - round(length * cos(rad));
		cub->player.dirY = cub->player.y - round(length * sin(rad));
		cub->player.difX = cub->player.dirX - cub->player.x;
		cub->player.difY = cub->player.dirY - cub->player.y;
		if (my_abs(cub->player.difX) > my_abs(cub->player.difY))
			cub->player.steps = my_abs(cub->player.difX);
		else
			cub->player.steps = my_abs(cub->player.difY);
		cub->player.x_inc = (float)cub->player.difX / (float)cub->player.steps;
		cub->player.y_inc = (float)cub->player.difY / (float)cub->player.steps;
		i = 0;
		y = cub->player.y;
		x = cub->player.x;
		i = 0;
		while (i < cub->player.steps)
		{
			if (check_wall(cub, round(x), round(y)))
				break;
			if (floor(angel) == floor(cub->player.angel))
				my_mlx_put_pixel(&cub->img, round(y), round(x), LINE_GREEN_COLOR);
			else
				my_mlx_put_pixel(&cub->img, round(y), round(x), LINE_COLOR);
			y += cub->player.y_inc;
			x += cub->player.x_inc;
			i++;
		}
		rays++;
		angel += 90.0 / cub->window_width;
	}
}


void	draw_player(t_cub3d *cub, int y_pos, int x_pos, int color)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	// while ()
	// {
		
	// }
	cub->player.x = x_pos;
	cub->player.y = y_pos;
	new_img(cub, cub->player.y, cub->player.x ,color, 5, 5);
	draw_line(cub);
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
				new_img(cub, y_pos, x_pos, WALL_COLOR, TILE_SIZE,
					TILE_SIZE);
			else
				new_img(cub, y_pos, x_pos, FLOOR_COLOR, TILE_SIZE,
					TILE_SIZE);
			x_pos += TILE_SIZE + 1;
		}
		y_pos += TILE_SIZE + 1;
	}
	draw_player(cub, cub->player.y, cub->player.x, PLAYER_COLOR);
	mlx_put_image_to_window(cub->mlx.mlxPtr, cub->mlx.win, cub->img.img, 0, 0);
	return (1);
}
