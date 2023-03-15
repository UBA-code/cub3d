/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:42:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/15 14:47:40 by ybel-hac         ###   ########.fr       */
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
	int	i;
	int	temp;

	i = 0;
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

void	recursion_check(char **map, int y, int x, char c)
{
	get_player_position(map, &y, &x, c);
	if (map[y][x + 1] && map[y][x + 1] != '1' && map[y][x + 1] != '*')
	{
		move_player(&(map[y][x + 1]), &(map[y][x]), c);
		recursion_check(map, 0, 0, c);
		move_back(&(map[y][x + 1]), &(map[y][x]), c);
	}
	if (map[y][x - 1] && map[y][x - 1] != '1' && map[y][x - 1] != '*')
	{
		move_player(&(map[y][x - 1]), &(map[y][x]), c);
		recursion_check(map, 0, 0, c);
		move_back(&(map[y][x - 1]), &(map[y][x]), c);
	}
	if (map[y + 1][x] && map[y + 1][x] != '1' && map[y + 1][x] != '*')
	{
		move_player(&(map[y + 1][x]), &(map[y][x]), c);
		recursion_check(map, 0, 0, c);
		move_back(&(map[y + 1][x]), &(map[y][x]), c);
	}
	if (map[y - 1][x] && map[y - 1][x] != '1' && map[y - 1][x] != '*')
	{
		move_player(&(map[y - 1][x]), &(map[y][x]), c);
		recursion_check(map, 0, 0, c);
		move_back(&(map[y - 1][x]), &(map[y][x]), c);
	}
}

int	check_surounded(char **map, char player)
{
	char	**dup_map;

	dup_map = get_dup_map(map);
	recursion_check(dup_map, 0, 0, player);
	tab_free(dup_map);
	return (1);
}

int	check_map(char **map)
{
	int		i;
	char	player;

	i = 0;
	player = get_player(map);
	check_characters(map);
	if (!check_surounded(map, player))
		return (0);
	return (1);
}

// 0 1 N S E W