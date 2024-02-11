/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:17:51 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/11 17:44:59 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'W' || c == 'E' || c == 'S'
		|| c == ' ' || c == '\n');
}

void    replace_spaces(char *line)
{
    int     i;
    int     size;

    if (!line)
        return ;
    size = ft_strlen(line);
    size--;
    while (is_space(line[size]))
        line[size--] = '$';
}

bool	is_line_valid(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!is_valid_map_char(line[i]))
			return (false);
	}
	return (true);
}

char    *skip_empty_lines(int cf_fd)
{
    char    *line;

    while (1)
    {
        line = gnl(cf_fd);
        if (!line)
            return (NULL);
        if (is_line_empty(line))
            free(line);
        else
            break;
    }
	if (!is_line_valid(line))
	{
		free (line);
		return (NULL);
	}
	printf ("HOPE NOT HERE\n");
    replace_spaces(line);
    return (line);
}

bool    read_map(t_cub *cub, int cf_fd)
{
    char    *long_line;
    char    *cur_line;

    cur_line = NULL;
    long_line = skip_empty_lines(cf_fd);
	if (!long_line)
		return (false);
    while (long_line)
    {
        cur_line = gnl(cf_fd);
        if (!cur_line)
            break ;
        if (!is_line_valid(cur_line) || is_line_empty(cur_line))
        {
            free_whatever("pp", long_line, cur_line);
            return (false);
        }
        replace_spaces(cur_line);
        long_line = append_str(long_line, cur_line, true);
    }
    cub->map_config.map = ft_split(long_line, '$');
    if (!cub->map_config.map)
        return (false);
	free_whatever("p", long_line);
    return (true);
}

bool    parse_map(t_cub *cub, int cf_fd)
{
    if (!read_map(cub, cf_fd))
        return (false);
    int i = -1;
    while (cub->map_config.map[++i])
        printf ("%s\n", cub->map_config.map[i]);
    return (true);
}