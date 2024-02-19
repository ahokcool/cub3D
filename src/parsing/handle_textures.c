/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:37:14 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/19 16:13:07 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Checks the rest of the textures */
static bool	check_rest(t_cub *cub, char **parts)
{
	if (!ft_strcmp(parts[0], "WE"))
	{
		if (cub->map_file.we_texture)
			return (false);
		cub->map_file.we_texture = ft_strdup(parts[1]);
	}
	else if (!ft_strcmp(parts[0], "EA"))
	{
		if (cub->map_file.ea_texture)
			return (false);
		cub->map_file.ea_texture = ft_strdup(parts[1]);
	}
	return (true);
}

/*
	Responsible for validation and assignment the texture parts of a config file
*/
bool	handle_texture_line(t_cub *cub, char **parts, int *found)
{
	if (!check_format(parts[1], ".xpm") || !file_exists(parts[1]))
		return (false);
	if (!ft_strcmp(parts[0], "NO"))
	{
		if (cub->map_file.no_texture)
			return (false);
		cub->map_file.no_texture = ft_strdup(parts[1]);
	}
	else if (!ft_strcmp(parts[0], "SO"))
	{
		if (cub->map_file.so_texture)
			return (false);
		cub->map_file.so_texture = ft_strdup(parts[1]);
	}
	else if (!check_rest(cub, parts))
		return (false);
	(*found)--;
	return (true);
}
