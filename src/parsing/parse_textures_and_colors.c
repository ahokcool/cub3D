/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_and_colors.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:31:58 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/19 16:39:50 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Checks if a key is one of the textures or color names */
static bool	is_texture_or_color(char *key, int flag)
{
	if (flag == 0)
	{
		return (!ft_strcmp(key, "NO") || !ft_strcmp(key, "SO")
			|| !ft_strcmp(key, "WE") || !ft_strcmp(key, "EA"));
	}
	else
		return (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"));
}

/* Prints an error message and frees memory */
static bool	parsing_error(t_cub *cub, char *error, char **parts)
{
	free_whatever("m", parts);
	ft_putendl_fd(error, 2);
	return (false);
}

/* Splits the string and validates substrings */
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
	if (part_count != 2 || !parts[0] || !parts[1])
	{
		free_whatever("m", parts);
		return (NULL);
	}
	return (parts);
}

/* Checks for the correct configuration of the components */
static bool	check_textures_colors(t_cub *cub, char *line, int *found)
{
	char	**parts;

	parts = prepare_parts(line);
	if (!parts)
		return (parsing_error(cub, "Wrong map file configuration!", parts));
	if (is_texture_or_color(parts[0], 0))
	{
		if (!handle_texture_line(cub, parts, found))
			return (parsing_error(cub, "Wrong texture format!", parts));
	}
	else if (is_texture_or_color(parts[0], 1))
	{
		if (!handle_color_line(cub, parts, found))
			return (parsing_error(cub, "Wrong color format!", parts));
	}
	else
		return (parsing_error(cub, "Unknown map components!", parts));
	free_whatever("m", parts);
	return (true);
}

/*
	Receives the fd of the configuration file
	
	Uses 'get_next_line' to read it line by line to handle textures and colors
	components
*/
bool	parse_textures_colors(t_cub *cub, int map_fd)
{
	char	*line;
	char	**parts;
	int		found;

	found = 6;
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
		if (!check_textures_colors(cub, line, &found))
			return (false);
	}
	return (true);
}
