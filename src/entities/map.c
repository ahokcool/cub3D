/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:58:53 by astein            #+#    #+#             */
/*   Updated: 2024/02/19 20:36:50 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_cub *cub)
{
	cub->map_file.no_texture = NULL;
	cub->map_file.so_texture = NULL;
	cub->map_file.we_texture = NULL;
	cub->map_file.ea_texture = NULL;
	cub->map_file.floor_clr.red = (uint8_t)260;
	cub->map_file.ceiling_clr.red = (uint8_t)260;
	cub->map_file.map = NULL;
}

void	free_map(t_cub *cub)
{
	if (cub->map_file.no_texture)
		free (cub->map_file.no_texture);
	if (cub->map_file.so_texture)
		free (cub->map_file.so_texture);
	if (cub->map_file.we_texture)
		free (cub->map_file.we_texture);
	if (cub->map_file.ea_texture)
		free (cub->map_file.ea_texture);
	if (cub->map_file.map)
		free_whatever("m", cub->map_file.map);
}

void	ini_cub(t_cub *cub)
{
	printf("ini_cub\n");
	cub->running = false;
	
	ini_win(&cub->win);
	ini_img(&cub->img_2d);
	ini_img(&cub->img_3d);
	ini_img(&cub->img_mini);
	init_map(cub);
	ini_player(&cub->player);
	ini_map2d(&cub->map2d);
	ini_map3d(&cub->map3d);
	ini_minimap(&cub->minimap);
	// ini_ray(cub->ray);
	ini_controller(&cub->controller);	
}
void	config_map(t_map_file *map, char *map_path)
{
	printf("config_map\n");
	// parsing ()
	(void)map_path;
	create_test_map(map);
	dbg_put_minimap_big(map->map);
}

void	destroy_map(t_map_file *map)
{
	(void)map;
	//TODO:	
}

