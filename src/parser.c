/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/02/02 18:43:50 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_format(char *path, char *expected_format)
{
	char	*file_format;

	file_format = ft_strrchr(path, '.');
	if (file_format && ft_strcmp(file_format, expected_format) == 0)
		return (true);
	return (false);
}

/* check if a character is one of the whitespaces */
bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\a'
		|| c == '\b' || c == '\f' || c == '\r');
}

static void	replace_whitespaces(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return ;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			line[i] = ' ';
	}
}

static bool	error_exit(char *error, char **components)
{
	free_whatever("m", components);
	ft_putendl_fd(error, 2);
	return (false);
}

bool	check_rgb_colors(char **rgb_parts)
{
	if (ft_size_matrix(rgb_parts) != 3 || !rgb_parts[0] || !rgb_parts[1] ||
		!rgb_parts[2])
	{	
		free_whatever("m", rgb_parts);
		return (false);
	}
	if (!ft_str_is_numeric(rgb_parts[0]) || !ft_str_is_numeric(rgb_parts[1]) || 
		!ft_str_is_numeric(rgb_parts[2]) || ft_atoi(rgb_parts[0]) < 0 || 
		ft_atoi(rgb_parts[0]) > 255 || ft_atoi(rgb_parts[1]) < 0 || 
		ft_atoi(rgb_parts[1]) > 255 || ft_atoi(rgb_parts[2]) < 0 || 
		ft_atoi(rgb_parts[2]) > 255)
	{	
		free_whatever("m", rgb_parts);
		return (false);
	}
	return (true);
}

void	assign_rgb(t_cub *cub, char **parts, char **rgb_colors, int flag)
{
	if (flag == 0)
	{
		cub->map_config.floor_clr.red = (uint8_t)ft_atoi(rgb_colors[0]); //TODO: cast
		cub->map_config.floor_clr.green = (uint8_t)ft_atoi(rgb_colors[1]);
		cub->map_config.floor_clr.blue = (uint8_t)ft_atoi(rgb_colors[2]);
	}
	else
	{
		cub->map_config.ceiling_clr.red = (uint8_t)ft_atoi(rgb_colors[0]);
		cub->map_config.ceiling_clr.green = (uint8_t)ft_atoi(rgb_colors[1]);
		cub->map_config.ceiling_clr.blue = (uint8_t)ft_atoi(rgb_colors[2]);
	}
	free_whatever("mm", rgb_colors, parts);
}

bool	validate_colors(t_cub *cub, char **parts, int *found)
{
	char	**rgb_colors;

	rgb_colors = ft_split(parts[1], ',');
	if (!rgb_colors || !check_rgb_colors(rgb_colors))
		return (false);
	if (!ft_strcmp(parts[0], "F"))
	{
		if (cub->map_config.floor_clr.red != (uint8_t)260)
		{
			free_whatever("m", rgb_colors);
			return (false);
		}
		assign_rgb(cub, parts, rgb_colors, 0);
	}
	else if (!ft_strcmp(parts[0], "C"))
	{
		if (cub->map_config.ceiling_clr.red != (uint8_t)260)
		{
			free_whatever("m", rgb_colors);
			return (false);
		}
		assign_rgb(cub, parts, rgb_colors, 1);
	}
	(*found)--;
	return (true);
}

bool	file_exists(const char *path)
{
    int	fd;

	fd = open(path, O_RDONLY);
    if (fd == -1) 
        return (false);
    close(fd);
    return (true);
}

bool	validate_textures(t_cub *cub, char **parts, int *found)
{
	if (!check_format(parts[1], ".xpm") || !file_exists(parts[1]))
		return (false);
	if (!ft_strcmp(parts[0], "NO"))
	{
		if (cub->map_config.no_texture)
			return (false);
		cub->map_config.no_texture = parts[1];
	}
	else if (!ft_strcmp(parts[0], "SO"))
	{
		if (cub->map_config.so_texture)
			return (false);
		cub->map_config.so_texture = parts[1];
	}
	else if (!ft_strcmp(parts[0], "WE"))
	{
		if (cub->map_config.we_texture)
			return (false);
		cub->map_config.we_texture = parts[1];
	}
	else if (!ft_strcmp(parts[0], "EA"))
	{
		if (cub->map_config.ea_texture)
			return (false);
		cub->map_config.ea_texture = parts[1];
	}
	free_whatever("p", parts[0]);
	(*found)--;
	return (true);
}

bool	empty_line(char *line)
{
	replace_whitespaces(line);
    while (*line)
	{
        if (!ft_isspace((unsigned char)*line))
            return (false);        
		line++;
    }
    return (true);
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
		if (empty_line(line))
		{
			free_whatever("p", line);
			continue ;
		}
		parts = prepare_parts(line);
		if (!parts)
			return (error_exit("Wrong map file configuration!", parts));
		if (parts[0] && (!ft_strcmp(parts[0], "NO") || !ft_strcmp(parts[0], "SO") || //TODO: move these 2 checks to a separated function
			!ft_strcmp(parts[0], "WE") || !ft_strcmp(parts[0], "EA")))
		{
			if (!validate_textures(cub, parts, &found))
				return (error_exit("Wrong texture format!", parts));
		}
		else if (parts[0] && (!ft_strcmp(parts[0], "F") || !ft_strcmp(parts[0], "C")))
		{
			if (!validate_colors(cub, parts, &found))
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
