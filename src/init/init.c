/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:51:23 by bahbibe           #+#    #+#             */
/*   Updated: 2023/06/12 15:17:23 by bahbibe          ###   ########.fr       */
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
		if (line[0] != '\n')
			cub->lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	cub->full_file = malloc(sizeof(char *) * (cub->lines + 1));
	cub->map = malloc(sizeof(char *) * (cub->lines - 5));
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
		if (line[0] != '\n')
			cub->full_file[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	cub->full_file[i] = NULL;
	close(fd);
	cub->info_size = 6;
	init_infos(cub);
}

