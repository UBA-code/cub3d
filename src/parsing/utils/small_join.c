/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:30:08 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/12 16:30:12 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	*strjoin_small(char *s1, char c)
{
	char	*final_str;
	int		total_len;
	int		i;

	i = 0;
	total_len = get_str_len(s1) + 1;
	final_str = ft_calloc(sizeof(char), (total_len + 2));
	if (!final_str)
		return (0);
	if (!s1)
		s1 = get_substring("", 0);
	ft_strcpy(final_str, s1);
	i = get_str_len(final_str);
	final_str[i] = c;
	final_str[i + 1] = 0;
	free(s1);
	return (final_str);
}
