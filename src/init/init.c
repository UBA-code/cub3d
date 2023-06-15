/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:51:23 by bahbibe           #+#    #+#             */
/*   Updated: 2023/06/15 13:19:26 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**alloc_file(t_cub3d *cub, int fd)
{
	char	*line;

	cub->lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		cub->lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	cub->full_file = ft_calloc(sizeof(char *), cub->lines + 1);
	cub->map = ft_calloc(sizeof(char *), (cub->lines - 5));
	if (!cub->full_file || !cub->map)
		return (close(fd), NULL);
	return (close(fd), cub->full_file);
}

int	check_args(t_cub3d *cub, int ac, char *file)
{
	int	fd;
	int	pos;

	if (ac != 2)
		return (ft_error("Usage: ./cub3d <map_file.cub>\n"), 0);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
		return (ft_error("Is a directory\n"), close(fd), 0);
	pos = ft_strlen(file) - 4;
	if (ft_strncmp(file + pos, ".cub", 4))
		return (ft_error("Invalid file <*.cub>\n"), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error("Cannot read file\n"), close(fd), 0);
	cub->full_file = alloc_file(cub, fd);
	return (1);
}

void	init_cub(t_cub3d *cub, char *file)
{
	int		i ;
	int		fd ;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_info(line))
			break;
		if (line[0] != '\n')
			cub->full_file[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		cub->full_file[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	init_infos(cub);
}

int is_info(char *line)
{
	if (!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2)
		|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

char *dup_line(char *src, int len)
{
	char *dst;
	int i ;
	int j ;

	i  = -1;
	dst = ft_calloc(sizeof(char), len);
	while (++i < len - 1)
		dst[i] = 'x';
	i = 0;
	j = -1;
	while (src && src[++j])
	{
		i++;
		if (in_set(src[j], "NWES01"))
			dst[i] = src[j];
	}
	return(dst);
}

char **dup_map(t_cub3d *cub)
{
	char **dup;
	int i;

	dup = ft_calloc(sizeof(char *) , cub->map_height + 3);
	dup[0] = dup_line(NULL, cub->map_width + 3);
	i = 0;
	while (++i < cub->map_height + 2)
		dup[i] = dup_line(cub->map[i - 1], cub->map_width + 3);
	dup[i - 1] = dup_line(NULL, cub->map_width + 3);
	return(dup);
}


int	is_closed(t_cub3d *cub)
{
	char **dup;
	int y;
	int x;

	y = -1;
	dup = dup_map(cub);
	while (dup[++y])
	{
		x  = -1;
		while (dup[y][++x])
		{
			if (dup[y][x] == 'x')
			{
				if((dup[y][x + 1] && !in_set(dup[y][x + 1], "x1"))
					|| (dup[y + 1] && !in_set(dup[y + 1][x], "x1")))
					return (0);
				if((x != 0 && !in_set(dup[y][x - 1], "x1"))
					||(y != 0 && !in_set(dup[y - 1][x], "x1")))
					return (0);
			}
		}
	}
	tab_free(dup);
	return (1);
}

int	check_token(t_cub3d *cub)
{
	int	count;
	int	x;
	int	y;
	
	count = -1;
	y = -1;
	while (cub->map[++y])
	{	
		x = -1;
		while (cub->map[y][++x])
		{
			if (in_set(cub->map[y][x], "NWES"))
			{
				cub->p = cub->map[y][x];
				count++;
			}
			else if(!in_set(cub->map[y][x], " NWES01\t"))
				ft_error("Invalid token\n");
		}
	}
	return(count);
}


void	check_map(t_cub3d *cub)
{
	if(!is_closed(cub))
		ft_error("Invalid map\n");
	if(check_token(cub))
		ft_error("Invalid position\n");
	if (cub->p == 'N')
		cub->player.angel = 90;
	if (cub->p == 'E')
		cub->player.angel = 180;
	if (cub->p == 'S')
		cub->player.angel = 270;
	if (cub->p == 'W')
		cub->player.angel = 0;
}