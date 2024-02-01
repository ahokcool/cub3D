/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/02/01 16:30:29 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_map(char **map)
{
	(void)map;
	//flood fill or something
	return(false);
}

static bool	check_format(char *path, char *expected_format)
{
	char	*file_format;

	file_format = ft_strrchr(path, '.');
	if (file_format && ft_strcmp(file_format, expected_format) == 0)
		return (true);
	return (false);
}

/* if it is one of the whitespaces */
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

static void	free_matrix(void **matrix)
{
	int	arr_i;

	arr_i = 0;
	if (matrix)
	{
		while (matrix[arr_i])
		{
			free(matrix[arr_i]);
			arr_i++;
		}
		free(matrix);
	}
}

static bool	error_exit(char *error, char *line, char **components)
{
	if (line)
		free (line);
	free_matrix(components);
	ft_putendl_fd(2, error);
	return (false);
}

static char	**prepare_line(char *line)
{
	char	**parts;
	int		part_count;

	replace_whitespaces(line);
	parts = ft_split(line, ' ');
	if (!parts)
		return (NULL);
	part_count = ft_size_matrix(parts);
	if (part_count != 2)
	{
		if (line)
			free(line);
		free_matrix(parts);
		return (NULL);
	}
	return (parts);
}

bool	validate_colors(t_cub *cub, char **parts, int *found)
{
	char	**rgb_parts;

	if (!parts)
		return (false);
	rgb_parts = ft_split(parts[1], ',');
	if (!rgb_parts || ft_size_matrix(rgb_parts) != 3 || !rgb_parts[0] || 
		!rgb_parts[1] || !rgb_parts[2])
		return (false);
	if (!ft_isdigit(rgb_parts[0]) || !ft_isdigit(rgb_parts[1]) || 
		!ft_isdigit(rgb_parts[2]) || ft_atoi(rgb_parts[0]) < 0 || 
		ft_atoi(rgb_parts[0]) > 255 || ft_atoi(rgb_parts[1]) < 0 || 
		ft_atoi(rgb_parts[1]) > 255 || ft_atoi(rgb_parts[2]) < 0 || 
		ft_atoi(rgb_parts[2]) > 255)
	{
		free_matrix(rgb_parts);
		return (false);
	}
	if (!ft_strcmp(parts[0], "F"))
	{
		if (cub->map_config.floor_clr.checked)
		{
			free_matrix(rgb_parts);
			return (false);
		}
		cub->map_config.floor_clr.param = parts[1];
		cub->map_config.floor_clr.checked = true;
	}
	else if (!ft_strcmp(parts[0], "C"))
	{
		if (cub->map_config.ceiling_clr.checked)
		{
			free_matrix(rgb_parts);
			return (false);
		}
		cub->map_config.ceiling_clr.param = parts[1];
		cub->map_config.ceiling_clr.checked = true;
	}
	*found--;
}

bool	file_exists(const char *path)
{
    int	fd;

	fd = open(path, O_RDONLY);
    if (fd == -1) 
        return false;
    close(fd);
    return true;
}


bool	validate_textures(t_cub *cub, char **parts, int *found)
{
	if (!parts)
		return (false);
	if (!ft_strcmp(parts[0], "NO"))
	{
		if (cub->map_config.no_texture.checked || 
		!check_format(parts[1], ".xpm") || !file_exists(parts[1]))
			return (false);
		cub->map_config.no_texture.param = parts[1];
		cub->map_config.no_texture.checked = true;
	}
	else if (!ft_strcmp(parts[0], "SO"))
	{
		if (cub->map_config.so_texture.checked || 
		!check_format(parts[1], ".xpm") || !file_exists(parts[1]))
			return (false);
		cub->map_config.so_texture.param = parts[1];
		cub->map_config.so_texture.checked = true;
	}
	else if (!ft_strcmp(parts[0], "WE"))
	{
		if (cub->map_config.we_texture.checked || 
		!check_format(parts[1], ".xpm") || !file_exists(parts[1]))
			return (false);
		cub->map_config.we_texture.param = parts[1];
		cub->map_config.we_texture.checked = true;
	}
	else if (!ft_strcmp(parts[0], "EA"))
	{
		if (cub->map_config.ea_texture.checked || 
		!check_format(parts[1], ".xpm") || !file_exists(parts[1]))
			return (false);
		cub->map_config.ea_texture.param = parts[1];
		cub->map_config.ea_texture.checked = true;
	}
	*found--;
	return (true);
}

static bool	validate_map_config_part1(t_cub *cub, int map_fd)
{
	char	*line;
	char	**parts;
	int		found;

	found = 6;
	while (found >= 0)
	{
		line = gnl(map_fd);
		if (!line)
			return (false);
		parts = prepare_line(line);
		if (!parts)
			return (error_exit("Wrong map file configuration!", line, parts));
		if (parts[0] && (!ft_strcmp(parts[0], "F") || !ft_strcmp(parts[0], "C")))
		{
			if (!validate_colors(cub, parts, &found))
				return (error_exit("Wrong color format", line, parts));
		}
		else if (parts[0] && (!ft_strcmp(parts[0], "NO") || !ft_strcmp(parts[0], "SO") || 
			!ft_strcmp(parts[0], "WE") || !ft_strcmp(parts[0], "EA")))
		{
			if (!validate_textures(cub, parts, &found))
				return (error_exit("Wrong texture format", line, parts));
		}
		else
			return (error_exit("Unknown map components!", line, parts));
	}
	return (validate_map_config_part2(cub, map_fd));
}

bool parse(t_cub *cub, char *path)
{
	(void)cub;
	char	*map_content;
	int		map_fd;

	if (!check_format(path, ".cub"))
		return (false);
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		return (false);
	validate_map_config_part1(cub, map_fd);
	



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
	
	// return (check_map(cub->map));
	return (false);
}
