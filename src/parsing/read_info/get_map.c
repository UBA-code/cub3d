/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:38:43 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/12 18:21:19 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	get_map_size(char **file, int *i)
{
	int	len;
	int	x;

	len = 0;
	--*i;
	while (file[++*i])
		if (check_empty(file[*i]) && !check_end_infos(file[*i]))
			break ;
	x = *i;
	while (file[x])
	{
		len++;
		++x;
	}
	return (len);
}

char	**get_map(t_cub3d cub)
{
	int		i;
	char	**map;
	int		x;

	x = 0;
	i = 0;
	map = ft_calloc(sizeof(char *), get_map_size(cub.full_file, &i) + 1);
	while(cub.full_file[i])
	{
		if (cub.full_file[i][0] == '\n')
			ft_error("the map has empty line inside\n");
		map[x++] = cub.full_file[i];
		i++;
	}
	return (map);
}
