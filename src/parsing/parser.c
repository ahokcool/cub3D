/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/02/03 13:58:27 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	error_exit(char *error, char **parts)
{
	free_whatever("m", parts);
	ft_putendl_fd(error, 2);
	return (false);
}

static char	**prepare_parts(char *line)
{
	char	**parts;
	int		part_count;

	replace_whitespaces(line);
	parts = ft_split(line, ' ');
	if (!parts)
		return (NULL);
	free_whatever("p", line);
	part_count = ft_size_matrix(parts);
	if (part_count != 2)
	{
		free_whatever("m", parts);
		return (NULL);
	}
	return (parts);
}

bool	is_texture_or_color(char *param, int flag)
{
	if (flag == 0)
	{
		return (!ft_strcmp(param, "NO") || !ft_strcmp(param, "SO")
			|| !ft_strcmp(param, "WE") || !ft_strcmp(param, "EA"));
	}
	else
	{
		return (!ft_strcmp(param, "F") || !ft_strcmp(param, "C"));
	}
}

static bool	check_textures_and_colors(t_cub *cub, int map_fd)
{
	char	*line;
	char	**parts;
	int		found;

	found = 6;
	parts = NULL;
	while (found > 0)
	{
		line = gnl(map_fd);
		if (!line)
			return (false);
		if (is_line_empty(line))
		{
			free_whatever("p", line);
			continue ;
		}
		parts = prepare_parts(line);
		if (!parts)
			return (error_exit("Wrong map file configuration!", parts));
		if (parts[0] && is_texture_or_color(parts[0], 0))
		{
			if (!check_and_assign_textures(cub, parts, &found))
				return (error_exit("Wrong texture format!", parts));
		}
		else if (parts[0] && is_texture_or_color(parts[0], 1))
		{
			if (!check_and_assign_colors(cub, parts, &found))
				return (error_exit("Wrong color format!", parts));
		}
		else
			return (error_exit("Unknown map components!", parts));
	}
	return (true);
}

static bool	check_map(char **map)
{
	(void)map;
	//flood fill or something
	return(false);
}

bool parse(t_cub *cub, char *path)
{
	char	*map_content;
	int		map_fd;

	if (!check_format(path, ".cub"))
		return (false);
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		return (false);
	if (!check_textures_and_colors(cub, map_fd))
		return (false);
	
	


	// open file
	// get next line
	
	// looooong str where u add the line via gnl and add a | at the end of each line
	// also count amount of lines
	// loop is done
	
	//looong_str = append_str(looong_str, line);
	//looong_str = append_str(looong_str, "|";
	
	// malloc maps first diminsion from the lines count
	// split by |
	// loop for each splt
	// malloc second diminsion from the length of the split
	
	// fill matrix

// 1 1 1 1 1 1 
// 1 1 1 1 1 1 1 1 1 
// 1 1 1 1 1 1 
// 1 1 1 1 1 1 1 1 1 1 1 1 1 
// 1 1 1 1 1 1 
// 1 1 1 1 1 1 

	
	// close file
	return (false);
	// return (check_map(cub->map));
}
