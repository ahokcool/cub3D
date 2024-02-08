/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:52:12 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 20:29:08 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map3d(t_map3d *map3d)
{
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
		ini_column(&map3d->columns[i]);
}

void	config_map3d(t_map3d *map3d, t_player *player)
{
	(void)map3d;
	(void)player;
}

void	update_map3d(t_map3d *map3d, t_player *player, t_map_config *map_config)
{
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
	{
		update_column(&map3d->columns[i], player, map_config, i);
	}
}

void	update_map3d_frame(t_cub *cub)
{
	int i;
	int y;
	// int height;
	int y_start;
	int y_end;
	int screen_middle_y;
	int wall_color;

	i = 0;
	screen_middle_y = WIN_HEIGHT / 2 - 1;
	while (i < WIN_WIDTH)
	{
		if (cub->map3d.columns[i].hit_direction == 'N')
			wall_color = (int)CLR_NORTH;
		else if (cub->map3d.columns[i].hit_direction == 'S')
			wall_color = (int)CLR_SOUTH;
		else if (cub->map3d.columns[i].hit_direction == 'E')
			wall_color = (int)CLR_EAST;
		else if (cub->map3d.columns[i].hit_direction == 'W')
			wall_color = (int)CLR_WEST;
		
		y_start = fmax(0, screen_middle_y - (cub->map3d.columns[i].height / 2));
		y_end = fmin(WIN_HEIGHT - 1, screen_middle_y + (cub->map3d.columns[i].height / 2));
		y = -1;
		// Draw sky
		while (++y < y_start)
    		if (y >= 0 && y < WIN_HEIGHT)
        		set_pixel_to_image(&cub->img_3d, i, y, CLR_SKY);
		
		// Draw wall
		y--;
		while (++y <= y_end) // Ensure y is within the screen bounds
    		if (y >= 0 && y < WIN_HEIGHT)
        		set_pixel_to_image(&cub->img_3d, i, y, wall_color);

		// Draw floor
		y--;
		while (++y < WIN_HEIGHT)
    		set_pixel_to_image(&cub->img_3d, i, y, CLR_FLOOR);

		i++;
	}
}