/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:42:25 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 19:02:38 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map2d(t_map2d *map2d)
{
	map2d->map_2d = NULL;
	ini_img(&map2d->img_wall);
	ini_img(&map2d->img_floor);
}

void	config_map2d(t_cub *cub, t_map2d *map2d)
{
	map2d->map_2d = cub->map_file.map;
	config_img_file(cub, &map2d->img_wall, "./textures/map2d/wall.xpm");
	config_img_file(cub, &map2d->img_floor, "./textures/map2d/floor.xpm");
}

void	destroy_map2d(void *mlx_ptr, t_map2d *map2d)
{
	destroy_img(mlx_ptr, map2d->img_wall.mlx_img);
	destroy_img(mlx_ptr, map2d->img_floor.mlx_img);
	free_whatever("m", map2d->map_2d);
}
