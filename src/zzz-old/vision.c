/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:50:44 by astein            #+#    #+#             */
/*   Updated: 2024/02/05 14:18:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_vision(t_cub *cub)
{
	angleToVector(cub->player.rot_angle, &cub->ray.v_direction);
	cub->ray.v_plane.x = sin(FOV / 2);
	cub->ray.v_plane.y = 0;

}

// void	draw_line()
