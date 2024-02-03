/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:29:38 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/03 14:08:35 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_format(char *path, char *expected_format)
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

bool	file_exists(const char *path)
{
    int	fd;

	fd = open(path, O_RDONLY);
    if (fd == -1) 
        return (false);
    close(fd);
    return (true);
}

void	replace_whitespaces(char *line)
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

bool	is_line_empty(char *line)
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
