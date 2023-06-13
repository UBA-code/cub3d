/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:08:06 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/06/13 17:56:40 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	printing(char** s)
{
	int i= -1;
    while(s && s[++i])
        printf("{%s}\n", s[i]);
}


int	main(int ac, char **av)
{
	t_cub3d	cub;

	if (!check_args(&cub, ac, av[1]))
		exit(EXIT_FAILURE);
	init_cub(&cub, av[1]);
	
	// cub.info = get_infos();
	// cub.map = get_map(&cub);
	// check_info(cub);
	// check_map(cub.map, &cub);
	// check_colors(&cub);
	draw_2dmap(&cub);
	// printing(cub.map);
	// free_utils(cub);
	// while (1);
	return (0);
}



// void printing(char** s)
// {
// 	int i= -1;
//     while(s && s[++i])
//         printf("%s ", s[i]);
// }

// int main(void)
// {
// 	char **sp = ft_split("220,,,,,,,10 0,100", ",\t ");
// 	printing(sp);	
// }
// int	check_args(t_cub3d *cub, int ac, char *file)

// int	main(int ac, char **av)
// {
// 	t_cub3d	cub;

// 	if (ac != 2 || !check_args(&cub, ac ,av[1]))
// 		return (EXIT_FAILURE);
// 	init_cub_struct(&cub);
// 	cub.full_file = get_full_file(av[1]);
// 	cub.info = get_infos(&cub);
// 	cub.map = get_map(&cub);
// 	check_info(cub);
// 	check_map(cub.map, &cub);
// 	check_colors(&cub);
// 	draw_2dmap(&cub);
// 	free_utils(cub);
// 	return (0);
// }