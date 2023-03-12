/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:23:44 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/12 16:52:46 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_struct(char *line, t_info *info)
{
	int		i;
	char	*temp;
	int		len;
	int		x;

	i = 0;
	while (line[i] == ' ')
		i++;
	x = i;
	len = 0;
	while (line[x] != ' ' && ++x)
		len++;
	info->id = ft_substr(line, i, len);
	i = x;
	while (line[i] == ' ')
		++i;
	x = i;
	len = 0;
	while (line[x] != ' ' && ++x)
		len++;
	info->content = ft_substr(line, i, len);
}

int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_end_infos(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == ' ')
		;
	if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
		|| !ft_strncmp(line + i, "WE", 2) || !ft_strncmp(line + i, "EA", 2)
		|| !ft_strncmp(line + i, "C", 1) || !ft_strncmp(line + i, "F", 1))
		return (1);
	return (0);
}

t_info *get_infos(t_cub3d *cub)
{
	int		i;
	t_info	*info;
	char	*temp;
	int		x;

	x = 0;
	info = ft_calloc(sizeof(t_info), 6);
	i = 0;
	while (cub->full_file[i])
	{
		if (check_empty(cub->full_file[i]) && check_end_infos(cub->full_file[i]))
			init_struct(cub->full_file[i], &(info[x++]));
		i++;
	}
	cub->info_size = x;
	return (info);
}
