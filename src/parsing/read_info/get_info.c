/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:23:44 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/05 14:43:45 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_struct(char *line, t_info *info)
{
	int		i;
	int		len;
	int		x;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	x = i;
	len = 0;
	while (line[x] && line[x] != ' ' && ++x)
		len++;
	info->id = ft_substr(line, i, len);
	i = x;
	while (line[i] && line[i] == ' ')
		++i;
	x = i;
	len = 0;
	while (line[x] && line[x] != ' ' && line[x] != '\n' && ++x)
		len++;
	if (!len)
	{
		info->content = 0;
		return ;
	}
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
		|| !ft_strncmp(line + i, "C", 1) || !ft_strncmp(line + i, "F", 1)
		|| line[i] == '\n')
		return (1);
	return (0);
}

void	get_info_size(t_cub3d *cub)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cub->full_file[i])
	{
		if (check_empty(cub->full_file[i], 'N')
			&& check_end_infos(cub->full_file[i]))
			len++;
		if (check_empty(cub->full_file[i], 'N')
			&& !check_end_infos(cub->full_file[i]))
		{
			cub->info_size = len;
			return ;
		}
		i++;
	}
}

char	*get_info_value(t_cub3d *cub, const char *id)
{
	int	i;

	i = 0;
	while (i < cub->info_size)
	{
		if (ft_strcmp(cub->info[i].id, id))
			return (cub->info[i].content);
		i++;
	}
	return (0);
}

t_info	*get_infos(t_cub3d *cub)
{
	int		i;
	t_info	*info;
	int		x;

	x = 0;
	get_info_size(cub);
	info = ft_calloc(sizeof(t_info), cub->info_size);
	i = 0;
	while (cub->full_file[i])
	{
		if (check_empty(cub->full_file[i], 'N')
			&& check_end_infos(cub->full_file[i]))
			init_struct(cub->full_file[i], &(info[x++]));
		i++;
	}
	return (info);
}
