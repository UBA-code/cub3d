/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:38:28 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/17 16:37:40 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	check_info_name(t_info info)
{
	int	i;

	i = 0;
	if (ft_strlen(info.id) > 2)
		ft_error("info name has more than one character\n");
	while (info.id[i])
	{
		if (!ft_isalpha(info.id[i]))
			ft_error("check info name please\n");
		i++;
	}
}

void	check_duplicated(t_cub3d cub)
{
	int	i;
	int	x;

	i = 0;
	while (i < cub.info_size)
	{
		x = i + 1;
		while (x < cub.info_size)
		{
			if (ft_strcmp(cub.info[x].id, cub.info[i].id))
				ft_error("Duplicated info\n");
			x++;
		}
		i++;
	}
}

void	check_path_utils(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("\033[0;31m", 2);
		perror(file);
		free(file);
		exit(EXIT_FAILURE);
	}
	close(fd);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Is a Directory\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	check_path(t_cub3d cub)
{
	int		i;

	i = 0;
	while (i < cub.info_size)
	{
		if (cub.info[i].content[0] == '.')
		{
			if (cub.info[i].content[1] == '/')
				check_path_utils(cub.info[i].content);
			else
			{
				ft_putstr_fd(cub.info[i].content, 2);
				ft_error("\nnot a valid path");
			}
		}
		i++;
	}
}

void	check_info(t_cub3d cub)
{
	int	i;

	i = 0;
	while (i < cub.info_size)
	{
		check_info_name(cub.info[i]);
		i++;
	}
	check_duplicated(cub);
	if (i != 6)
		ft_error("info is not completed\n");
	check_path(cub);
}
