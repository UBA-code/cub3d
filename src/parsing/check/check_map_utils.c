/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:56:01 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/11 17:53:19 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_characters(t_cub3d *cub, char **map)
{
	int	y;
	int	x;
	int	player_count;

	y = 0;
	player_count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!(map[y][x] == '0' || map[y][x] == '1' || map[y][x] == 'N'
				|| map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W'
				|| map[y][x] == ' '))
				ft_error("check map characters please\n");
			if ((map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W') && ++player_count)
				cub->p = map[y][x];
			x++;
		}
		y++;
	}
	if (player_count != 1)
		ft_error("problem in number of player\n");
	return (1);
}

void	copy_map(char **dst, char *src, int len)
{
	int	i;
	int	x;

	x = -1;
	i = 0;
	*dst = ft_calloc(sizeof(char), len + 3);
	while (++x < len + 2)
		(*dst)[x] = 'x';
	x = 1;
	while (src[i])
	{
		if (src[i] == '\n')
			break ;
		if (src[i] == ' ')
			(*dst)[x] = 'x';
		else
			(*dst)[x] = src[i];
		x++;
		i++;
	}
}

void	move_back(char *c1, char *c2, char player)
{
	*c1 = '*';
	*c2 = player;
}
