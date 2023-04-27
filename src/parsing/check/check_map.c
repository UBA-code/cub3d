/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:42:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/27 19:54:38 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	**get_dup_map(char **map)
{
	int		big_len;
	int		i;
	int		x;
	char	**final;

	final = ft_calloc(sizeof(char *), get_tab_len(map) + 3);
	i = -1;
	x = 0;
	big_len = 0;
	while (map[++i])
		if (ft_strlen(map[i]) > (size_t)big_len)
			big_len = ft_strlen(map[i]);
	i = -1;
	copy_map(&(final[x++]), "", big_len);
	while (map[++i])
		copy_map(&(final[x++]), map[i], big_len);
	copy_map(&(final[x++]), "", big_len);
	return (final);
}

void	get_player_position(char **map, int *y, int *x, char c)
{
	int	temp;

	*y = 0;
	*x = 0;
	while (map[*y])
	{
		temp = ft_strchr_index(map[*y], c);
		if (temp != -1)
		{
			*x = temp;
			return ;
		}
		++*y;
	}
}

void	check_outside(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'x')
			{
				if (map[y][x + 1] && map[y][x + 1] != 'x'
					&& map[y][x + 1] != '1')
					ft_error("not surrounded\n");
				if (x != 0 && map[y][x - 1] && map[y][x - 1] != 'x'
					&& map[y][x - 1] != '1')
					ft_error("not surrounded\n");
				if (map[y + 1] && map[y + 1][x] != 'x' && map[y + 1][x] != '1')
					ft_error("not surrounded\n");
				if (y != 0 && map[y - 1] && map[y - 1][x] != 'x'
					&& map[y - 1][x] != '1')
					ft_error("not surrounded\n");
			}
		}
	}
}

int	check_surounded(char **map)
{
	char	**dup_map;

	dup_map = get_dup_map(map);
	check_outside(dup_map);
	tab_free(dup_map);
	return (1);
}

void	get_map_sizes(t_cub3d *cub)
{
	int	y;

	y = 0;
	cub->map_width = 0;
	while (cub->map[y])
	{
		if ((int)ft_strlen(cub->map[y]) > cub->map_width)
			cub->map_width = ft_strlen(cub->map[y]);
		y++;
	}
	cub->map_height = y;
}

void	get_player_states(t_cub3d *cub)
{
	if (cub->p == 'N')
		cub->player.angel = 90;
	if (cub->p == 'E')
		cub->player.angel = 180;
	if (cub->p == 'S')
		cub->player.angel = 270;
	if (cub->p == 'W')
		cub->player.angel = 0;
	
}

int	check_map(char **map, t_cub3d *cub)
{
	check_characters(cub, map);
	if (!check_surounded(map))
		return (0);
	get_map_sizes(cub);
	get_player_states(cub);
	return (1);
}

// 0 1 N S E W