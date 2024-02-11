/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:17:51 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/11 00:24:49 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    is_valid_map_char(char c, bool *found)
{
    if (*found == true)
    {
       if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
         *found = true;
    }
    else
        return (false);
    return (c == '0' || c == '1' || c == 'N' || c == 'W' || c == 'E'
        || c == 'S' || c == ' ');
}


// bool    parse_map(t_cub *cub, int cf_fd)
// {
//     char    line;
//     bool    valid;
//     bool    map_started;
//     bool    found_player;

//     valid = false;
//     map_started = false;
//     found_player = false;
//     while (valid != true)
//     {
//         line = gnl(cf_fd);
//         if (!line)
//             return (false);
//         if (is_line_empty(line) && !map_started)
// 		{
// 			free_whatever("p", line);
// 			continue ;
// 		}
//         else if (is_line_empty(line) && map_started)
//         {
//             free_whatever("p", line);
//             return (false);
//         }
//         if (!check_map_line(cub, line, &map_started, &found_player))
//             return (false);
//         free_whatever("p", line);
//     }
// }

// void    replace_space_tab(char *line)
// {
//     int i;
//     int count;

//     if (!line || !ft_strchr(line, ' '))
//         return ;
//     i = -1;
//     count = 0;
//     while (line[++i] == '\t')
//         count++;
//     printf ("COUNT %d\n", count);
// }

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
    replace_spaces(line);
    return (line);
}

bool    read_map(t_cub *cub, int cf_fd)
{
    char    *long_line;
    char    *cur_line;

    cur_line = NULL;
    long_line = skip_empty_lines(cf_fd);
    while (1)
    {
        cur_line = gnl(cf_fd);
        if (!cur_line)
            break ;
        if (is_line_empty(cur_line))
        {
            free_whatever("pp", long_line, cur_line);
            return (false);
        }
        replace_spaces(cur_line);
        // replace_space_tab(cur_line);
        long_line = append_str(long_line, cur_line, true);
    }
    cub->map_config.map = ft_split(long_line, '$');
    if (!cub->map_config.map)
        return (true);
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