/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:08:06 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/06/09 12:53:38 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"


// void	init_cub_struct(t_cub3d *cub)
// {
// 	cub->full_file = 0;
// 	cub->info = 0;
// 	cub->info_size = 0;
// 	cub->map = 0;
// }
int	ft_is_space(int c)
{	
	return (c == '\f' || c == '\n' || c == '\r' \
	|| c == '\t' || c == '\v' || c == ' ');
}
char	**alloc_file(t_cub3d *cub, int fd)
{
	char	*line;
	
	cub->lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		if(line[0] != '\n')
			cub->lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	cub->full_file = malloc(sizeof(char *) * (cub->lines + 1));
	if(!cub->full_file)
		return(close(fd), NULL);
	return(close(fd), cub->full_file);
}

void	init_cub(t_cub3d *cub, char *file)
{
	int		i ;
	int		fd ;
	char	*line;
	
	i = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if(line[0] != '\n')
			cub->full_file[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	cub->full_file[i] = NULL;
	close(fd);
	init_infos(cub);
}

char *valide_id(char *id)
{
	if (!ft_strcmp(id, "EA") || !ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || !ft_strcmp(id, "WE") || !ft_strcmp(id, "F") || !ft_strcmp(id, "C") )
		return id;
	return (NULL);
}
char	*valide_xpm(char *id, char *file)
{
	int fd;
	int i;
	char *split;
	
	if (id[0] == "F" || id[0] == "C")
	{
		split = ft_split(file, ',');
		i = 0;
		while (i < 3)
			if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255)
		
		
	}
	fd = open(ft_strtrim( file,"\n"), O_RDONLY);
	if (fd == -1)
		perror(file);
	return ( file);
}

char *parse_info( char *file, int flag)
{
	char	*id;
	char	*content;
	char	**split;

	split = f_split(file, ' ');	
	id = split[0];
	content = split[1];
	if (flag == ID)
		return (valide_id(id));
	else if (flag == CONTENT)
		return (valide_xpm( id, content));
	return (NULL);
}	

void	init_infos(t_cub3d *cub)
{
	int i = 0;
	
	while (i < 6)
	{
		printf("=====%s=====\n", parse_info( cub->full_file[i],ID));
		printf("%s", parse_info( cub->full_file[i],CONTENT));
		// cub->info[i].id = parse_info(cub->full_file[i],ID);
		// printf("%s\n", cub->info[i].id );
		// cub->info[i].content = parse_info(cub->full_file[i],CONTENT);
		// printf("%s\n", cub->info[i].content );
		i++;
	}
	
}

void printing(char** s)
{
	int i= -1;
    while(s && s[++i])
        printf("%s", s[i]);
}


int	check_args(t_cub3d *cub, int ac, char *file)
{
	int	fd;
	int	pos;

	if (ac != 2)
		return (ft_error("Usage: ./cub3d <map_file.cub>"), 0);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
		return (ft_error("Is a directory"), close(fd), 0);
	pos = ft_strlen(file) - 4;
	if (ft_strncmp(file + pos, ".cub", 4))
		return (ft_error("Invalid file <*.cub>"), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error("Cannot read file"), close(fd), 0);
	cub->full_file = alloc_file(cub, fd);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;

	if (!check_args(&cub, ac, av[1]))
		exit(EXIT_FAILURE);
	init_cub(&cub, av[1]);
	// printing(cub.full_file);
	
	// cub.info = get_infos();
	// cub.map = get_map(&cub);
	// check_info(cub);
	// check_map(cub.map, &cub);
	// check_colors(&cub);
	// draw_2dmap(&cub);
	// free_utils(cub);
	return (0);
}
