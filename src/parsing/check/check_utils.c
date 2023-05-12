/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:54:07 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/11 17:54:23 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	get_player_states(t_cub3d *cub)
{
	if (cub->p == 'N')
		cub->player.angel = 90;
	if (cub->p == 'E')
		cub->player.angel = 180;
	if (cub->p == 'S')
		cub->player.angel = 270;
	if (cub->p == 'W')
		cub->player.angel = 0;
}

int	check_map(char **map, t_cub3d *cub)
{
	check_characters(cub, map);
	if (!check_surounded(map))
		return (0);
	get_map_sizes(cub);
	get_player_states(cub);
	return (1);
}
