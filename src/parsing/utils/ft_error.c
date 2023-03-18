/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:37:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/18 16:18:41 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	ft_error(char *s)
{
	int	i;

	i = -1;
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\033[0;37m", 2);
	exit(EXIT_FAILURE);
}
