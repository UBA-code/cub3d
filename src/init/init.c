/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:51:23 by bahbibe           #+#    #+#             */
/*   Updated: 2023/06/14 17:37:42 by bahbibe          ###   ########.fr       */
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
	i = 1;
	j = -1;
	while (src && src[++j])
	{
		if (in_set(src[j], "01"))
			dst[i] = src[j];
		i++;
	}
	// dst[len] = 0;
	// if(src)
	// {
	// 	while (++i < len)
	// 	{
	// 		if (is_set(src[i], " \t"))
	// 			dst[i] = src[i];
	// 	}
	// 	free(src);
	// }
	return(dst);
}

char **dup_map(t_cub3d *cub)
{
	char **dup;
	int i;

	i = -1 ;
	dup = ft_calloc(sizeof(char *) , cub->map_height + 3);
	// dup[0] = dup_line(cub->map[0], cub->map_width + 3);
	while (++i < cub->map_height + 3)
	{
		if (i == 0 || i == cub->map_height + 2)
			dup[i] = dup_line(NULL, cub->map_width + 3);
		else if (i < cub->map_height)
			dup[i] = dup_line(cub->map[i], cub->map_width + 3);
		printf("%s\n", dup[i]);
	}
	return(dup);
}


int	is_closed(t_cub3d *cub)
{
	char **dup;

	dup = dup_map(cub);
	// printing(dup);
	return 0;
}

int	check_map(char **map, t_cub3d *cub)
{
	(void) map;
	is_closed(cub);
	// check_characters(cub, map);
	// if (!check_surounded(map))
	// 	return (0);
	// // get_map_sizes(cub);
	// get_player_states(cub);	 // ! keep it here
	return (1);
}