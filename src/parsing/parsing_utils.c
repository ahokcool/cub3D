/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:29:38 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/11 17:56:46 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Checks is the file has an expected format */
bool	check_format(char *path, char *expected_format)
{
	char	*file_format;

	file_format = ft_strrchr(path, '.');
	if (file_format && ft_strcmp(file_format, expected_format) == 0)
		return (true);
	return (false);
}

/* Checks if the character is one of the whitespaces */
bool	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\a'
		|| c == '\b' || c == '\f' || c == '\r');
}

/* Checks if the file exists */
bool	file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1) 
		return (false);
	close(fd);
	return (true);
}

/* 
	Traverses through the string and replaces all the whitespace characters by 
	spaces
 */
void	replace_whitespaces(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return ;
	while (line[++i])
	{
		if (is_space(line[i]))
			line[i] = ' ';
	}
}

/*
	Checks if the line is empty
*/
bool	is_line_empty(char *line)
{
	while (*line)
	{
		if (!is_space((unsigned char)*line))
			return (false);
		line++;
	}
	return (true);
}
