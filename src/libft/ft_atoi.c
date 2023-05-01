/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:43:28 by ybel-hac          #+#    #+#             */
/*   Updated: 2022/10/31 01:21:43 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	calc_skip(const char *s, int *i, int *sign_len, int *sign)
{
	*sign = 1;
	while ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == ' ')
		++*i;
	while (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
		{
			*sign = -1;
			++*sign_len;
		}
		else if (s[*i] == '+')
		{
			*sign = 1;
			++*sign_len;
		}
		++*i;
	}
}

static int	get_len(const char *str, int *i)
{
	int	len;
	int	x;

	x = *i;
	len = 0;
	while (str[x] == '0')
		x++;
	while (str[x] >= '0' && str[x] <= '9')
	{
		len++;
		x++;
	}
	return (len);
}

int	ft_atoi(const char *str)
{
	size_t	num;
	int		sign_len;
	int		sign;
	int		i;
	int		num_len;

	i = 0;
	sign_len = 1;
	num = 0;
	calc_skip(str, &i, &sign_len, &sign);
	num_len = get_len(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == -1 && sign_len <= 2 && num_len >= 20)
			return (0);
		else if (sign == 1 && sign_len <= 2 && num_len >= 20)
			return (-1);
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (sign_len > 2)
		return (0);
	return (num * sign);
}
