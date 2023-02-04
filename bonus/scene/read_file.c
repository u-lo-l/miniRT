/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:05:07 by dkim2             #+#    #+#             */
/*   Updated: 2022/10/28 11:10:22 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBFT/libft.h"
#include "scene.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "in_parsing.h"
#include "quadrics.h"

static int	parse_scene(const char *line)
{
	t_scene	*out_scene;
	char	**element;
	int		res;
	int		i;

	out_scene = get_scene();
	element = ft_split(line, " \t\v\r\f\n");
	if (!element)
		return (FALSE);
	if (ft_strsetlen(element) > 0)
	{
		if (ft_strncmp(element[0], "A", 2) == 0)
			res = case_ambient(out_scene, element);
		else if (ft_strncmp(element[0], "C", 2) == 0)
			res = case_camera(out_scene, element);
		else if (ft_strncmp(element[0], "L", 2) == 0)
			res = case_light(out_scene, element);
		else
			res = init_quadrics(out_scene, element);
	}
	i = 0;
	while (element[i])
		free (element[i++]);
	free(element);
	return (res);
}

static void	terminate_gnl(int fd, char *last_line)
{
	char	*line;

	printf("error line : %s\n", last_line);
	free(last_line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	check_scene( void )
{
	t_scene	*scene = get_scene();

	if (scene->ambient_ratio == 0)
	{
		printf("no amb\n");
		return (FALSE);
	}
	if (scene->cam == NULL)
	{
		printf("no cam\n");
		return (FALSE);
	}
	if (scene->light == NULL)
	{
		printf("no light\n");
		return (FALSE);
	}
	if (scene->quads == NULL)
	{
		printf("no obj\n");
		return (FALSE);
	}
	return (TRUE);
}

static int	check_filename(const char *filename)
{
	if (ft_strncmp(&filename[ft_strlen(filename) - 3], ".rt", 4))
		return (FALSE);
	return (TRUE);
}

int	scene_init(const char *filename)
{
	int		fd;
	char	*line;

	line = NULL;
	if (!check_filename(filename))
		return (FALSE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	while (TRUE)
	{
		free(line);
		line = get_next_line(fd);
		printf("line : <%s>\n", line);
		if (line == NULL)
			break ;
		else if (line[0] == '#')
			continue ;
		else if (ft_strncmp(line, "", 1) && !parse_scene(line))
		{
			terminate_gnl(fd, line);
			return (FALSE);
		}
	}
	close(fd);
	return (check_scene());
}
