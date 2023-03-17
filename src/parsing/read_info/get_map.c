/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:38:43 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/17 11:46:23 by ybel-hac         ###   ########.fr       */
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
		if (check_empty(file[*i], '0') && !check_end_infos(file[*i]))
			break ;
	x = *i;
	while (file[x])
	{
		len++;
		++x;
	}
	return (len);
}

void	map_copy(char **dst, char *src, char *next)
{
	int	i;

	i = -1;
	if (!next && src[ft_strlen(src) - 1] == '\n')
		ft_error("new line at end of map\n");
	*dst = ft_calloc(sizeof(char), ft_strlen(src) + 1);
	while (src[++i] && src[i] != '\n')
		(*dst)[i] = src[i];
}

char	**get_map(t_cub3d cub)
{
	int		i;
	char	**map;
	int		x;
	int		big_len;

	x = 0;
	i = 0;
	big_len = 0;
	map = ft_calloc(sizeof(char *), get_map_size(cub.full_file, &i) + 1);
	while (cub.full_file[i])
	{
		if (cub.full_file[i][0] == '\n')
			ft_error("the map has empty line inside\n");
		map_copy(&map[x++], cub.full_file[i], cub.full_file[i + 1]);
		i++;
	}
	return (map);
}
