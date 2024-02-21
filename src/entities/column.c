/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:17:03 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 18:05:49 by astein           ###   ########.fr       */
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
	column->wall_start_y = -1;
	column->wall_end_y = -1;
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

