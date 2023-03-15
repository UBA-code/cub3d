/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:34:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/15 14:45:03 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	get_tab_len(char **tab)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (tab[++i])
		len++;
	return (len);
}

char	**dup_tab(char **map)
{
	char	**final;
	int		i;
	int		x;

	i = 0;
	x = 0;
	final = ft_calloc(sizeof(char *), get_tab_len(map) + 1);
	while (map[i])
	{
		final[x] = ft_strdup(map[i]);
		i++;
		x++;
	}
	return (final);
}
