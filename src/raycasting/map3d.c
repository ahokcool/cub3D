/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:52:12 by astein            #+#    #+#             */
/*   Updated: 2024/02/09 19:58:10 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map3d(t_map3d *map3d)
{
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
		ini_column(&map3d->columns[i]);
	ini_img(&map3d->img_wall);
}

void	config_map3d(t_cub *cub, t_map3d *map3d, t_player *player)
{
	(void)map3d;
	(void)player;
	config_img_file(cub, &map3d->img_wall, "textures/testwall.xpm");
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

static void	draw_wall(t_cub *cub, int i, int y_end, int *y)
{
	int wall_color;

	if (cub->map3d.columns[i].hit_direction == 'N')
		wall_color = (int)CLR_NORTH;
	else if (cub->map3d.columns[i].hit_direction == 'S')
		wall_color = (int)CLR_SOUTH;
	else if (cub->map3d.columns[i].hit_direction == 'E')
		wall_color = (int)CLR_EAST;
	else if (cub->map3d.columns[i].hit_direction == 'W')
		wall_color = (int)CLR_WEST;

	(*y)--;
	if (cub->controller.show_texture)
	{
		// Draw wall
		// TODO:
		while (++(*y) <= y_end) // Ensure y is within the screen bounds
			;
	}
	else
	{
		while (++(*y) <= y_end) // Ensure y is within the screen bounds
    		if (*y >= 0 && *y < WIN_HEIGHT)
        		set_pixel_to_image(&cub->img_3d, i, *y, wall_color);
		
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

	i = 0;
	screen_middle_y = WIN_HEIGHT / 2 - 1;
	while (i < WIN_WIDTH)
	{
		
		
		y_start = fmax(0, screen_middle_y - (cub->map3d.columns[i].height / 2));
		y_end = fmin(WIN_HEIGHT - 1, screen_middle_y + (cub->map3d.columns[i].height / 2));
		y = -1;
		// Draw sky
		while (++y < y_start)
    		if (y >= 0 && y < WIN_HEIGHT)
        		set_pixel_to_image(&cub->img_3d, i, y, CLR_SKY);
		
		// Draw wall
		draw_wall(cub, i, y_end, &y);
		

		// Draw floor
		y--;
		while (++y < WIN_HEIGHT)
    		set_pixel_to_image(&cub->img_3d, i, y, CLR_FLOOR);

		i++;
	}
}