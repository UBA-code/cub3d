/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:08:06 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/06/17 23:07:58 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d	cub;

	if (!check_args(&cub, ac, av[1]))
		exit(EXIT_FAILURE);
	init_cub(&cub, av[1]);
	draw_2dmap(&cub);
	free_utils(cub);
	return (0);
}
