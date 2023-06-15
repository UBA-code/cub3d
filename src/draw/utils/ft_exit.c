/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:19:27 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/13 15:30:52 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	ft_exit(t_cub3d *cub, int error)
{
	int	i;

	i = -1;
	(void)cub;
	while (++i < cub->info_size)
	{
		free(cub->info[i].content);
		free(cub->info[i].id);
	}
	free(cub->info);
	tab_free(cub->full_file);
	tab_free(cub->map);
	i = -1;
	exit(error);
}

int	exit_btn(t_cub3d *cub)
{
	ft_exit(cub, 0);
	return (1);
}
