/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/02/03 16:02:42 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_map(char **map)
{
	(void)map;
	//flood fill or something
	return(false);
}

bool parse(t_cub *cub, char *path)
{
	char	*map_content;
	int		map_fd;

	if (!check_format(path, ".cub"))
		return (false);
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		return (false);
	if (!parse_textures_colors(cub, map_fd))
		return (false);
	// ---------------------------------- test ---------------------------------
	// printf ("TEXTURES: \n NO - %s\n SO - %s\n WE - %s\n EA - %s\n", 
	// 	cub->map_config.no_texture, cub->map_config.so_texture,
	// 	cub->map_config.we_texture, cub->map_config.ea_texture);
	// printf ("COLORS: \n Floor: \n Red - %d\n Green - %d\n Blue - %d\n \
	// 				 \n Ceiling: \n Red - %d\n Green - %d\n Blue - %d\n",
	// 		cub->map_config.floor_clr.red, cub->map_config.floor_clr.green, cub->map_config.floor_clr.blue,
	// 		cub->map_config.ceiling_clr.red, cub->map_config.ceiling_clr.green, cub->map_config.ceiling_clr.blue);
	// -------------------------------------------------------------------------
	
	
	
	// return (check_map(cub->map));
	return (false);
}
