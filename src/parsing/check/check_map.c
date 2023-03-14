/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:42:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/14 22:34:22 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == ' '))
			return (0);
		i++;
	}
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
			break;
		if (src[i] == ' ')
			(*dst)[x] = 'x';
		else
			(*dst)[x] = src[i];
		x++;
		i++;
	}
	(*dst)[ft_strlen(*dst) - 1] = '\n';
}

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
		if (ft_strlen(map[i]) > big_len)
			big_len = ft_strlen(map[i]);
	i = -1;
	copy_map(&(final[x++]), "", big_len);
	while (map[++i])
		copy_map(&(final[x++]), map[i], big_len);
	copy_map(&(final[x++]), "", big_len);
	return (final);
}

void	move_player(char *c1, char *c2, int y, int x)
{
	if (*c1 == 'x')
		return (ft_error("Map not sourrended by walls\n"));
	*c1 = 'N';
	*c2 = '*';
}

typedef struct s_recursion_utils
{
	int	y;
	int	x;
	char **mp;
}	t_recursion_utils;

void	recursion_check(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = ft_strchr_index(map[y], 'N'); // check here on character N
		if (x == -1)
			continue ;
		if (map[y][x + 1] && map[y][x + 1] != '1' && map[y][x + 1] != '*')
		{
			move_player(&(map[y][x + 1]), &(map[y][x]), y, x + 1);
			// if (map[y][x + 1] == 'x')
			// 	return (ft_error("Map not sourrended by walls\n"));
			// map[y][x + 1] = 'N';
			// map[y][x] = '*';
			recursion_check(map);
			map[y][x + 1] = '*';
		}
		if (map[y][x - 1] && map[y][x - 1] != '1' && map[y][x - 1] != '*')
		{
			move_player(&(map[y][x - 1]), &(map[y][x]), y, x - 1);
			// if (map[y][x - 1] == 'x')
			// 	return (ft_error("Map not sourrended by walls\n"));
			// map[y][x - 1] = 'N';
			// map[y][x] = '*';
			recursion_check(map);
			map[y][x - 1] = '*';
		}
		if (map[y + 1][x] && map[y + 1][x] != '1' && map[y + 1][x] != '*')
		{
			move_player(&(map[y + 1][x]), &(map[y][x]), y + 1, x);
			// if (map[y + 1][x] == 'x')
			// 	return (ft_error("Map not sourrended by walls\n"));
			// map[y + 1][x] = 'N';
			// map[y][x] = '*';
			recursion_check(map);
			map[y + 1][x] = '*';
		}
		if (map[y - 1][x] && map[y - 1][x] != '1' && map[y - 1][x] != '*')
		{
			move_player(&(map[y - 1][x]), &(map[y][x]), y - 1, x);
			// if (map[y - 1][x] == 'x')
			// 	return (ft_error("Map not sourrended by walls\n"));
			// map[y - 1][x] = 'N';
			// map[y][x] = '*';
			recursion_check(map);
			map[y - 1][x] = '*';
		}
	}
}
// 34
int	check_surounded(char **map)
{
	char **dup_map;

	dup_map = get_dup_map(map);
	recursion_check(dup_map);
	int	i = 0;
	tab_free(dup_map);
	return (0);
}

int	check_map(char **map)
{
	int	i;

	i = 0;
	if (!check_surounded(map))
		return (0);
	while (map[i])
	{
		if (!check_characters(map[i]))
			ft_error("check map characters please\n");
		i++;
	}
	return (1);
}

// 0 1 N S E W