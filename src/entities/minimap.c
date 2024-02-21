/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:19:58 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 17:56:41 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_minimap(t_minimap *minimap)
{
	ini_img(&minimap->img_wall);
	ini_img(&minimap->img_floor);
	minimap->map_mini = NULL;
	minimap->size = -1;
} 

void	config_minimap(t_cub *cub, t_minimap *minimap, char **map)
{
	t_vector_int	dim;

	minimap->size = 2 * MINIMAP_BORDER_SIZE + 1;
	ft_matrix_dim(map, &dim.x, &dim.y);
	if (minimap->size > dim.x)
		minimap->size = dim.x;
	if (minimap->size > dim.y)
		minimap->size = dim.y;
	config_img_file(cub, &minimap->img_wall, "./textures/minimap/wall.xpm");
	config_img_file(cub, &minimap->img_floor, "./textures/minimap/floor.xpm");
}

void	destroy_minimap(void *mlx_ptr, t_minimap *minimap)
{
	destroy_img(mlx_ptr, minimap->img_wall.mlx_img);
	destroy_img(mlx_ptr, minimap->img_floor.mlx_img);
	free_whatever("m", minimap->map_mini);
}

void	update_mapmini_frame(t_cub *cub)
{
	(void)cub;
}
