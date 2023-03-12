/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:42:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/12 18:24:17 by ybel-hac         ###   ########.fr       */
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

int	check_map(char **map)
{
	int	i;

	i = 0;
	// if (!check_surounded(map))
		
	while (map[i])
	{
		if (!check_characters(map[i]))
			ft_error("check map characters please\n");
		i++;
	}
	return (1);
}

// 0 1 N S E W