/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:05:05 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 19:17:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_map3d(t_map3d *map3d, t_player *player, t_map_file *map_file)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		update_column(&map3d->columns[i], player, map_file, i);
}

void	update_map3d_frame(t_cub *cub)
{
	int	x_screen;
	int	y;

	x_screen = 0;
	while (x_screen < WIN_WIDTH)
	{
		y = 0;
		while (y < cub->map3d.columns[x_screen].wall_start_y)
		{
			set_pixel_to_image(&cub->img_3d, x_screen, y,
				cub->map_file.rgb_ceiling);
			y++;
		}
		draw_wall(cub, x_screen);
		y = cub->map3d.columns[x_screen].wall_end_y;
		while (y < WIN_HEIGHT)
		{
			set_pixel_to_image(&cub->img_3d, x_screen, y,
				cub->map_file.rgb_floor);
			y++;
		}
		x_screen++;
	}
}
