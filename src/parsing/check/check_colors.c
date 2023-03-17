/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:34:24 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/17 16:36:36 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	check_color(char *color)
{
	char	**tab;
	int		i;
	int		count;
	int		temp;

	count = 0;
	tab = ft_split(color, ',');
	i = -1;
	while (tab[++i])
	{
		temp = 0;
		while (tab[i][temp])
		{
			if (!ft_isdigit(tab[i][temp]))
				return (tab_free(tab), ft_error("non digit color\n"));
			temp++;
		}
		temp = ft_atoi(tab[i]);
		if (temp > 255 || temp < 0)
			return (tab_free(tab), ft_error("check rgb range please\n"));
		count++;
	}
	if (count != 3)
		ft_error("uncompeleted color\n");
	tab_free(tab);
}

void	check_colors(t_cub3d *cub)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < cub->info_size)
	{
		if (cub->info[i].content[0] != '.' && cub->info[i].content[0] != '/')
		{
			check_color(cub->info[i].content);
			count++;
		}
		i++;
	}
	if (count != 2)
		ft_error("colors is more or less than 2\n");
}
