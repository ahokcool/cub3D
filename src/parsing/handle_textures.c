/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:37:14 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/03 15:50:06 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool    check_rest(t_cub *cub, char **parts)
{
    if (!ft_strcmp(parts[0], "WE"))
	{
		if (cub->map_config.we_texture)
			return (false);
		cub->map_config.we_texture = ft_strdup(parts[1]);
	}
	else if (!ft_strcmp(parts[0], "EA"))
	{
		if (cub->map_config.ea_texture)
			return (false);
		cub->map_config.ea_texture = ft_strdup(parts[1]);
	}
    return (true);
}

bool	handle_texture_line(t_cub *cub, char **parts, int *found)
{
	if (!check_format(parts[1], ".xpm") || !file_exists(parts[1]))
		return (false);
	if (!ft_strcmp(parts[0], "NO"))
	{
		if (cub->map_config.no_texture)
			return (false);
		cub->map_config.no_texture = ft_strdup(parts[1]);
	}
	else if (!ft_strcmp(parts[0], "SO"))
	{
		if (cub->map_config.so_texture)
			return (false);
		cub->map_config.so_texture = ft_strdup(parts[1]);
	}
    else if (!check_rest(cub, parts))
        return (false);
	(*found)--;
	return (true);
}
