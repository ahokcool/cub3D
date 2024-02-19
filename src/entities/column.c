/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:17:03 by astein            #+#    #+#             */
/*   Updated: 2024/02/19 19:35:10 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_column(t_pixel_column *column)
{
	column->perp_distance_to_wall = 0;
	column->height = 0;
	column->hit_direction = 0;
	column->hit_pos.x = -1;
	column->hit_pos.y = -1;
	column->ray.x = 0;
	column->ray.y = 0;
}

void	config_column(t_pixel_column *column)
{
	(void)column;
		// TODO:
}

void	destroy_column(t_pixel_column *column)
{
	(void)column;
		// TODO:
}

void	update_column(t_pixel_column *column, t_player *player, t_map_file *map_file, int column_index)
{
	double cameraX;
	// double fovAdjustment = player->fov / 50.0;

	cameraX = ((2 * column_index / (double)WIN_WIDTH) - 1);
	cameraX = ((2 * column_index / (double)WIN_WIDTH) - 1);

	column->ray.x = player->dir.x + player->v_plane.x * cameraX; //* player->fov;	//TODO: SCROLING OUT OF VIEW IS NOT WORKING
	column->ray.y = player->dir.y + player->v_plane.y * cameraX; //* player->fov;	//TODO: SCROLING OUT OF VIEW IS NOT WORKING
	
	// for test draw
	column->ray.x *= 20;
	column->ray.y *= 20;
	
	// DDA FOR WALL COALISION
	t_vector_int	tile_index;
	t_vector_int	step;
	t_vector_dbl	sideDist;
	t_vector_dbl	deltaDist;
	double	perpWallDist;
	int	hit = 0;
	int	side;
	
	tile_index.x = (int)player->pos.x;
	tile_index.y = (int)player->pos.y;
	deltaDist.x = fabs(1 / column->ray.x);
	deltaDist.y = fabs(1 / column->ray.y);
	if (column->ray.x < 0)
	{
		step.x = -1;
		sideDist.x = (player->pos.x - tile_index.x) * deltaDist.x;
	}
	else
	{
		step.x = 1;
		sideDist.x = (tile_index.x + 1.0 - player->pos.x) * deltaDist.x;
	}
	
	if (column->ray.y < 0)
	{
		step.y = -1;
		sideDist.y = (player->pos.y - tile_index.y) * deltaDist.y;
	}
	else
	{
		step.y = 1;
		sideDist.y = (tile_index.y + 1.0 - player->pos.y) * deltaDist.y;
	}

	while (!hit)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			tile_index.x += step.x;
			side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			tile_index.y += step.y;
			side = 1;
		}
		if (map_file->map[tile_index.y][tile_index.x] == '1')
			hit = 1;
	}

	if (side == 0)
		perpWallDist = (tile_index.x - player->pos.x + (1 - step.x) / 2) / column->ray.x;
	else
		perpWallDist = (tile_index.y - player->pos.y + (1 - step.y) / 2) / column->ray.y;

	// try

	//  //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	// if(side == 0)
	// 	perpWallDist = (sideDist.x - deltaDist.x);
	// else
	// 	perpWallDist = (sideDist.y - deltaDist.y);
	// // 


	column->perp_distance_to_wall = perpWallDist;
	column->height = (int)((1 / perpWallDist) * (double)WALL_HEIGHT);
	if (side == 0)
	{
		if (column->ray.x > 0)
			column->hit_direction = 'W';
		else
			column->hit_direction = 'E';	
	}
	else
	{
		if (column->ray.y > 0)
			column->hit_direction = 'N';
		else
			column->hit_direction = 'S';	
	}
	column->hit_pos.x = player->pos.x + column->perp_distance_to_wall * column->ray.x;
	column->hit_pos.y = player->pos.y + column->perp_distance_to_wall * column->ray.y;
	// printf("height: %d\n", column->height);

	// Calculate where the Wall was hit
	column->wall_x = column->hit_pos.x;
	column->wall_x -= floor(column->wall_x);
	
}

