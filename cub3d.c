/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:08:06 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/04/13 16:01:44 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	init_cub_struct(t_cub3d *cub)
{
	cub->full_file = 0;
	cub->info = 0;
	cub->info_size = 0;
	cub->map = 0;
}

int	check_args(char *file)
{
	int	fd;

	if (!ft_strcmp(ft_strrchr(file, '.'), ".cub"))
		return (ft_error("check extention of file\n"), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), 0);
	close(fd);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		ft_error(file);
		ft_error(": is a directory\n");
		return (close(fd), 0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;

	if (ac != 2 || !check_args(av[1]))
		return (EXIT_FAILURE);
	init_cub_struct(&cub);
	cub.full_file = get_full_file(av[1]);
	cub.info = get_infos(&cub);
	cub.map = get_map(&cub);
	int i = 0;
	check_info(cub);
	check_map(cub.map, &cub);
	check_colors(&cub);
	while (i < cub.info_size)
	{
		printf("%s", cub.info[i].id);
		printf("%s\n", cub.info[i].content);
		i++;
	}
	i = 0;
	while (cub.map[i])
	{
		printf("%s\n", cub.map[i]);
		i++;
	}
	printf("width: %d, heigth: %d\n", cub.map_width, cub.map_height);
	free_utils(cub);
	return (0);
}
