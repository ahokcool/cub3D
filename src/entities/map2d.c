/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:42:25 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 17:49:22 by astein           ###   ########.fr       */
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
	map2d->map_2d = NULL;
	config_img_file(cub, &map2d->img_wall, "./textures/map2d/wall.xpm");
	config_img_file(cub, &map2d->img_floor, "./textures/map2d/floor.xpm");
}

void	destroy_map2d(void *mlx, t_map2d *map2d)
{
	mlx_destroy_image(mlx, map2d->img_wall.mlx_img);
	mlx_destroy_image(mlx, map2d->img_floor.mlx_img);
	free_whatever("m", map2d->map_2d);
}
//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



// void	update_map2d_frame(t_cub *cub)
// {
// 		// put_wall(cub, 0, 0);
// 	int	i;
// 	int	x;
// 	int	y;

// 	i = 0;
// 	x = 0;
// 	y = 0;

// 	//DRAW MAP
// 	while (cub->map[y])
// 	{
// 		x = 0;
// 		while (cub->map[y][x])
// 		{
// 			if(cub->map[y][x] == '1')
// 				put_tile(cub, x * MAP2D_PIXEL_WIDTH, y * MAP2D_PIXEL_WIDTH, &cub->map2d.wall, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 			else
// 				put_tile(cub, x * MAP2D_PIXEL_WIDTH, y * MAP2D_PIXEL_WIDTH, &cub->map2d.empty, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 			x++;
// 		}
// 		y++;
// 	}

// 	// DRAW PLAYER
// 	if (cub->player.rot_angle == 0)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_N, &cub->img_2d, MINIMAP_PIXEL_WIDTH);
// 	else if (cub->player.rot_angle == 45)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_NE, &cub->img_2d, MINIMAP_PIXEL_WIDTH);
// 	else if (cub->player.rot_angle == 90)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_E, &cub->img_2d, MINIMAP_PIXEL_WIDTH);
// 	else if (cub->player.rot_angle == 135)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_SE, &cub->img_2d, MINIMAP_PIXEL_WIDTH);
// 	else if (cub->player.rot_angle == 180)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_S, &cub->img_2d, MINIMAP_PIXEL_WIDTH);
// 	else if (cub->player.rot_angle == 225)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_SW, &cub->img_2d, MINIMAP_PIXEL_WIDTH);
// 	else if (cub->player.rot_angle == 270)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_W, &cub->img_2d, MINIMAP_PIXEL_WIDTH);
// 	else if (cub->player.rot_angle == 315)
// 		put_tile(cub, (int)(cub->player.pos_x*MAP2D_PIXEL_WIDTH), (int)(cub->player.pos_y*MAP2D_PIXEL_WIDTH), &cub->minimap.player_NW, &cub->img_2d, MINIMAP_PIXEL_WIDTH);


// 	// {
	
// 	// 	if(cub->minimap.mini_map_str[i] == '1')
// 	// 		put_tile(cub, x, y, &cub->map2d.empty, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 	else if(cub->minimap.mini_map_str[i] == 'P')
// 	// 	{
// 	// 		if (cub->player.rot_angle == 0)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_N, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 		else if (cub->player.rot_angle == 45)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_NE, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 		else if (cub->player.rot_angle == 90)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_E, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 		else if (cub->player.rot_angle == 135)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_SE, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 		else if (cub->player.rot_angle == 180)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_S, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 		else if (cub->player.rot_angle == 225)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_SW, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 		else if (cub->player.rot_angle == 270)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_W, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 		else if (cub->player.rot_angle == 315)
// 	// 			put_tile(cub, x, y, &cub->minimap.player_NW, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 	}
// 	// 	else
// 	// 		put_tile(cub, x, y, &cub->map2d.empty, &cub->img_2d, MAP2D_PIXEL_WIDTH);
// 	// 	x += MAP2D_PIXEL_WIDTH;
// 	// 	if(x >= cub->img_mini.width)
// 	// 	{
// 	// 		y += MAP2D_PIXEL_WIDTH;
// 	// 		x = 0;
// 	// 	}
// 	// 	i++;
// 	// }	

// 	x = 0;
// 	int x_put;
// 	int y_put;
// 	while(x < cub->win.win_width)
// 	{
// 		x_put = x;
// 		y_put = ((double)MAP2D_PIXEL_WIDTH / 2 + cub->colums[x].y_hit_pos*MAP2D_PIXEL_WIDTH);
	
// 		// printf("drawing hit point at x: %d y: %d\n", x, y);
// 		put_pixel_to_image(cub, cub->win.mlx, cub->img_2d.mlx_img, x, y_put, 0xFFFFFF);
// 		x++;
// 	}
	
	
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	printf("----\n");
// }