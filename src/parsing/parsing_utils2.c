/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:13 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/16 20:04:29 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Checks if a recieving char is a valid map char */
bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'W' || c == 'E' || c == 'S'
		|| c == ' ' || c == '\n');
}

/* Checks if the line consists only of valid map characters */
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

/* 
	Iterates from the end of a recieving string and replaces all the whitespace 
	characters by '$' for simpler splitting later on
*/
void	replace_spaces(char *line)
{
	int	i;
	int	size;

	if (!line)
		return ;
	size = ft_strlen(line);
	size--;
	while (is_space(line[size]))
		line[size--] = '$';
}

/* 
	The recieving string is a concatenated string of the whole map which will be
	splitted after

	It checks if there's a single valid player character 
*/
bool	validate_player(char *str)
{
	bool	found;
	int		i;

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
	if (!found)
		return (false);
	return (true);
}
