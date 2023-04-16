/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:56:01 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/15 21:32:25 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_characters(char **map)
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
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count > 1)
		ft_error("more than one player\n");
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
	// (*dst)[ft_strlen(*dst) - 1] = '\n';
}

char	get_player(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strchr_index(map[i], 'N') != -1)
			return ('N');
		if (ft_strchr_index(map[i], 'S') != -1)
			return ('S');
		if (ft_strchr_index(map[i], 'E') != -1)
			return ('E');
		if (ft_strchr_index(map[i], 'W') != -1)
			return ('W');
		i++;
	}
	ft_error("No player found\n");
	return (0);
}

void	move_back(char *c1, char *c2, char player)
{
	*c1 = '*';
	*c2 = player;
}
