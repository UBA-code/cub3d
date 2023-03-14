/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:38:43 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/13 22:51:12 by ybel-hac         ###   ########.fr       */
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

void	map_copy(char **dst, char *src, int len)
{
	int	i;

	i =-1;
	*dst = ft_calloc(sizeof(char), len + 1);
	while (src[++i])
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
	// while(cub.full_file[i])
	// {
	// 	if (ft_strlen(cub.full_file[i]) > big_len)
	// 		big_len = ft_strlen(cub.full_file[i]);
	// 	i++;
	// }
	// i = 0;
	while(cub.full_file[i])
	{
		if (cub.full_file[i][0] == '\n')
			ft_error("the map has empty line inside\n");
		// map_copy(&(map[x++]), cub.full_file[i], big_len);
		map[x++] = cub.full_file[i];
		i++;
	}
	return (map);
}
