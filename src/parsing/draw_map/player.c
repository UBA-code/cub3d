/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:03:12 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/11 10:25:47 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_player(t_cub3d *cub)
{
	int	y;
	int	x;
	float	y_pos;
	float	x_pos;

	y_pos = 0;
	y = -1;
	// cub->player.angel = ANGEL;
	cub->player.turn_speed = TURN_SPEED;
	cub->player.walk_speed = PLAYER_SPEED;
	cub->player.walk = 0;
	cub->player.turn = 0;
	while (cub->map[++y])
	{
		x = -1;
		x_pos = 0;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == cub->p)
			{
				cub->player.x = x_pos + (TILE_SIZE / 2);
				cub->player.y = y_pos + (TILE_SIZE / 2);
				return ;
			}
			x_pos += TILE_SIZE;
		}
		y_pos += TILE_SIZE;
	}
}

int	wall_height(float distance, float wall_height, int screen_height)
{
    int wall_pixels;

	wall_pixels = (int)((wall_height * screen_height) / (distance));
    return (wall_pixels);
}

void	draw_walls(t_cub3d *cub, float y, float x, float angel, int start_x)
{
	float	dist;
	float	wall_len;
	int		start_y;
	int		text_start_pixel;
	int		offsetY;
	float	real_wall_len;

	dist = sqrt((int)pow(x - cub->player.x , 2) + (int)pow(y - cub->player.y, 2));
	dist = dist * cos(cub->player.angel * (PI / 180.0) - angel * (PI / 180.0));
	wall_len = wall_height(dist, TILE_SIZE, WINDOW_HEIGTH);
	real_wall_len = wall_len;
	if (wall_len > WINDOW_HEIGTH)
		wall_len = WINDOW_HEIGTH;
	start_y = (WINDOW_HEIGTH - wall_len) / 2.0;
	text_start_pixel = (WINDOW_HEIGTH - real_wall_len) / 2.0;
	while (wall_len-- > 0)
	{
		if (cub->player.direction == NO) 
		{
			offsetY = (start_y - text_start_pixel) * ((float)cub->textures[NO].heigth / real_wall_len);
			my_mlx_put_pixel(&cub->map_img,
				start_y, start_x, cub->textures[NO].addr[(cub->textures[NO].width * offsetY) + (int)x % TILE_SIZE]);
		}
		else if (cub->player.direction == EA)
		{
			offsetY = (start_y - text_start_pixel) * ((float)cub->textures[EA].heigth / real_wall_len);
			my_mlx_put_pixel(&cub->map_img,
				start_y, start_x, cub->textures[EA].addr[(cub->textures[EA].width * offsetY) + (int)y % TILE_SIZE]);
		}
		else if (cub->player.direction == SO)
		{
			offsetY = (start_y - text_start_pixel) * ((float)cub->textures[SO].heigth / real_wall_len);
			my_mlx_put_pixel(&cub->map_img,
				start_y, start_x, cub->textures[SO].addr[(cub->textures[SO].width * offsetY) + (int)x % TILE_SIZE]);
		}
		else if (cub->player.direction == WE)
		{
			offsetY = (start_y - text_start_pixel) * ((float)cub->textures[WE].heigth / real_wall_len);
			my_mlx_put_pixel(&cub->map_img,
				start_y, start_x, cub->textures[WE].addr[(cub->textures[WE].width * offsetY) + (int)y % TILE_SIZE]);
		}
		start_y++;
	}
} 


void	check_direction(t_cub3d *cub, float y, float x)
{
	y -= cub->player.y_inc;
	x -= cub->player.x_inc;
	if (check_wall(cub, x, y + cub->player.y_inc) && cub->player.y_inc <= 0)
		cub->player.direction = NO;
	else if (check_wall(cub, x + cub->player.x_inc, y) && cub->player.x_inc <= 0)
		cub->player.direction = WE;
	else if (check_wall(cub, x, y + cub->player.y_inc))
		cub->player.direction = SO;
	else if (check_wall(cub, x + cub->player.x_inc, y))
		cub->player.direction = EA;
}

void	draw_line(t_cub3d *cub)
{
	float	y;
	float	x;
	int		i;
	float	rad;
	int		length;
	float	angel;
	int		rays;
	float	dist;
	float	wall_len;
	int 	start_y;
	int 	start_x;

	length = 1000000000;
	rays = -1;
	angel = cub->player.angel - 30.0;
	start_x = 0;
	while (++rays < WINDOW_WIDTH)
	{
		rad = angel * (PI / 180.0);
		cub->player.dirX = cub->player.x - floor(length * cos(rad));
		cub->player.dirY = cub->player.y - floor(length * sin(rad));
		cub->player.difX = cub->player.dirX - cub->player.x;
		cub->player.difY = cub->player.dirY - cub->player.y;
		cub->player.steps = my_abs(cub->player.difY);
		if (my_abs(cub->player.difX) > my_abs(cub->player.difY))
			cub->player.steps = my_abs(cub->player.difX);
		cub->player.x_inc = cub->player.difX / cub->player.steps;
		cub->player.y_inc = cub->player.difY / cub->player.steps;
		i = 0;
		y = cub->player.y;
		x = cub->player.x;
		i = 0;
		while (i < cub->player.steps && !check_wall(cub, (x), (y)))
		{
			if ((angel) == (cub->player.angel))
				my_mlx_put_pixel(&cub->img, floor(y) * SCALE_SIZE, floor(x) * SCALE_SIZE, LINE_COLOR);
			y += cub->player.y_inc;
			x += cub->player.x_inc;
			i++;
		}
		check_direction(cub, y, x);
		draw_walls(cub, y, x, angel, start_x);
		start_x++;
		angel += 60.0 / WINDOW_WIDTH;
	}
}

void	draw_player(t_cub3d *cub, float y_pos, float x_pos, int color)
{
	cub->player.x = x_pos;
	cub->player.y = y_pos;
	new_img(&cub->img, cub->player.y * SCALE_SIZE, cub->player.x * SCALE_SIZE, color, 3,
		3);
	draw_line(cub);
}
