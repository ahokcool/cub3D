/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:17:51 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/19 16:17:23 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*  */
char	*skip_empty_lines(int cf_fd)
{
	char	*line;

	while (1)
	{
		line = gnl(cf_fd);
		if (!line)
			return (NULL);
		if (is_line_empty(line))
			free(line);
		else
			break ;
	}
	if (!is_line_valid(line))
	{
		free (line);
		return (NULL);
	}
	replace_spaces(line);
	return (line);
}

char	*read_map(t_cub *cub, int cf_fd)
{
	char	*long_line;
	char	*cur_line;

	cur_line = NULL;
	long_line = skip_empty_lines(cf_fd);
	if (!long_line)
		return (NULL);
	while (long_line)
	{
		cur_line = gnl(cf_fd);
		if (!cur_line || is_line_empty(cur_line))
		{
			free_whatever("p", cur_line);
			break ;
		}
		if (!is_line_valid(cur_line))
		{
			free_whatever("pp", long_line, cur_line);
			return (NULL);
		}
		replace_spaces(cur_line);
		long_line = append_str(long_line, cur_line, true);
	}
	return (long_line);
}

bool	check_borders(t_cub *cub, int i, int j)
{
	if (j == 0 || i == 0 || !cub->map_file.map[i + 1]
		|| !cub->map_file.map[i][j + 1]
		|| !cub->map_file.map[i][j - 1]
		|| !cub->map_file.map[i - 1][j]
		|| !cub->map_file.map[i + 1][j]
		|| (cub->map_file.map[i][j - 1] && cub->map_file.map[i][j - 1] == ' ')
		|| (cub->map_file.map[i][j + 1] && cub->map_file.map[i][j + 1] == ' ')
		|| (cub->map_file.map[i - 1][j] && cub->map_file.map[i - 1][j] == ' ')
		|| (cub->map_file.map[i + 1][j] && cub->map_file.map[i + 1][j] == ' '))
	{
		return (false);
	}
	return (true);
}

bool	handle_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map_file.map[++i])
	{
		j = 0;
		while (cub->map_file.map[i][j])
		{
			if (cub->map_file.map[i][j] != '1' 
				&& cub->map_file.map[i][j] != ' ')
			{
				if (!check_borders(cub, i, j))
					return (false);
			}
			j++;
		}
	}
	return (true);
}

bool	parse_map(t_cub *cub, int cf_fd)
{
	char	*map_line;

	map_line = read_map(cub, cf_fd);
	if (!map_line)
		return (false);
	if (!validate_player(map_line))
	{
		free_whatever("p", map_line);
		return (false);
	}
	cub->map_file.map = ft_split(map_line, '$');
	free_whatever("p", map_line);
	if (!cub->map_file.map)
		return (false);
	if (!handle_map(cub))
		return (false);
	printf ("CORRCT\n");
	return (true);
}
