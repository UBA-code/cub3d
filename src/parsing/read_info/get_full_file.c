/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:28:17 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/09 17:53:53 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	get_lines_len(char *file)
{
	int		fd;
	char	*temp;
	int		len;

	fd = open(file, O_RDONLY);
	len = 0;
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break;
		if (check_empty(temp))
			len++;
		free(temp);
	}
	close(fd);
	return (len);
}

char	**get_full_file(char *file)
{
	char	**full_file;
	int		fd;
	char	*temp;
	int		i;

	full_file = ft_calloc(sizeof(char *), get_lines_len(file) + 1);
	fd = open(file, O_RDONLY);
	i = 0;
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break;
		full_file[i++] = temp;
	}
	close(fd);
	return (full_file);
}
