/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:17:51 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/16 14:18:14 by anshovah         ###   ########.fr       */
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
    replace_spaces(line);
    return (line);
}

bool    validate_player(char *str)
{
    bool    found;
    int     i;

    found = false;
    i = -1;
    while (str[++i])
    {
        if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
        {
            if (found)
                return (false);
            found = true;
        }
    }
    return (true);
}

char    *read_map(t_cub *cub, int cf_fd)
{
    char    *long_line;
    char    *cur_line;

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

bool    parse_map(t_cub *cub, int cf_fd)
{
    char    *map_line;

    map_line = read_map(cub, cf_fd);  
    if (!map_line)
        return (false);
    if (!validate_player(map_line))
    {
        free_whatever("p", map_line);
        return (false);
    }
    cub->map_config.map = ft_split(map_line, '$');
    free_whatever("p", map_line);
    if (!cub->map_config.map)
        return (false);
    printf ("CORRECT\n");
    return (true);
}

// int i = -1;
// int i = -1;
// while (map[++i])
//    j = -1;
//    while (map[i][++j]
// nt i = -1;
// while (map[++i])
//    j = -1;
//    while (map[i][++j]
//   {


//    }
// int i = -1;
// while (map[++i])
//    j = -1;
//    while (map[i][++j]
//   {
//        if (map[i][++j] != ' ' || map[i][++j] != '1'
//               check all neighbor cells (top, bottom, left, right)
//    }
// nt i = -1;
// while (map[++i])
//    j = -1;
//    while (map[i][++j]
//   {
//        if (map[i][++j] != ' ' || map[i][++j] != '1' 
//              if (i == 0 || !map[i][j] || i == map hight - 1 || j == 0
//                       its not valid
//               check all neighbor cells (top, bottom, left, right)
//    }
// int i = -1;
// while (map[++i])
//    j = -1;
//    while (map[i][++j]
//   {
//        if (map[i][++j] != ' ' || map[i][++j] != '1' 
//            continue ;
//        if (i == 0 || !map[i][j] || i == map hight - 1 || j == 0
//                  its not valid
//             check all neighbor cells (top, bottom, left, right)
//    }
// the last one id the right one
// int i = -1;
// while (map[++i])
//    j = -1;
//    while (map[i][++j]
//   {
//        if (map[i][++j] != ' ' || map[i][++j] != '1' 
//            continue ;
//        if (i == 0 || !map[i][j + 1] || i == map hight - 1 || j == 0
//                  its not valid
//             check all neighbor cells (top, bottom, left, right)
//    }