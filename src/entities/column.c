/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:17:03 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 16:23:42 by astein           ###   ########.fr       */
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

