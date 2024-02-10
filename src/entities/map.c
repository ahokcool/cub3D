/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:58:53 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 16:24:40 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map(t_map_config *map)
{
	map->map = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_clr = (t_color){-1, -1, -1};
	map->ceiling_clr = (t_color){-1, -1, -1};
}
void	config_map(t_map_config *map, char *map_path)
{
	printf("config_map\n");
	// parsing ()
	(void)map_path;
	create_test_map(map);
	dbg_put_minimap_big(map->map);
}

void	destroy_map(t_map_config *map)
{
	(void)map;
	//TODO:	
}
