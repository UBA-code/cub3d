/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:38:26 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/05/12 19:51:33 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_empty(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (c == 'N' && line[i] != ' ' && line[i] != '\n')
			return (1);
		if (c != 'N' && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	my_abs(int x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}
