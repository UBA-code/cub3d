/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:05:26 by bahbibe           #+#    #+#             */
/*   Updated: 2023/06/13 17:00:54 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*valide_id(char *id)
{
	if (ft_strcmp(id, "EA") || ft_strcmp(id, "NO")
		|| ft_strcmp(id, "SO") || ft_strcmp(id, "WE")
		|| ft_strcmp(id, "F") || ft_strcmp(id, "C"))
		return (id);
	ft_error("Invalid id\n");
	return (NULL);
}

int	valide_color(char *rgb)
{
	char	**split;
	int		count;
	int		i;
	int		len;

	i = -1 ;
	count = 0 ;
	while (rgb[++i])
	{
		if (rgb[i] == ',' && rgb[i + 1] == ',')
			return (0);
		else if (rgb[i] == ',')
			count++;
		else if (rgb[i] != ',' && !ft_isdigit(rgb[i]))
			return (0);
	}
	split = ft_split_set(rgb, " ,\t\n", &len);
	if (len != 3)
		ft_error("Invalid color\n");
	while (--len >= 0)
		if (ft_atoi(split[len]) < 0 || ft_atoi(split[len]) > 255)
			ft_error("Invalid color\n");
	tab_free(split);
	return (count);
}

char	*valide_content( char *content, char *id)
{
	int		fd;
	char	*file;

	fd = -1;
	file = ft_strtrim(content, " \t\n");
	free(content);
	if (*id == 'F' || *id == 'C')
	{
		if (valide_color(file) != 2)
			ft_error("Invalid color\n");
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			ft_error("Cannot open xpm file\n");
	}
	return (close(fd), file);
}

void	parse_info( t_info *inf, char *file, int i)
{
	char	*id;
	char	*content;

	while (ft_is_space(*file))
		file++;
	id = ft_substr(file, 0, ft_strchr_index(file, " \t"));
	content = ft_substr(file + ft_strlen(id), 0, ft_strlen(file));
	inf[i].id = valide_id(id);
	inf[i].content = valide_content(content, inf[i].id);
}	

void	init_infos(t_cub3d *cub)
{
	int	i;
	int	j;
	int	x;

	i = -1;
	x = 0;
	cub->info = ft_calloc(sizeof(t_info), 6);
	while (++i < 6)
		parse_info(cub->info, cub->full_file[i], i);
	j = -1;
	while (++j < 6)
	{
		x = j;
		while (++x < 6)
			if (ft_strcmp(cub->info[j].id, cub->info[x].id))
				ft_error("Duplicate infos\n");
	}
	parse_map(cub, i);
}

void	parse_map(t_cub3d *cub, int i)
{
	int j;

	j = -1;
	cub->map_width = 0;
	while (cub->full_file[i])
	{
		if (ft_strlen(cub->full_file[i]) > (size_t)cub->map_width)
			cub->map_width = ft_strlen(cub->full_file[i]);
		cub->map[++j] = ft_substr(cub->full_file[i], 0,
			ft_strchr_index(cub->full_file[i], "\n"));
		i++;
	}
	cub->map_height = i;
	check_map(cub->map, cub);
}
