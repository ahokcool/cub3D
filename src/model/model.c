/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:26:36 by astein            #+#    #+#             */
/*   Updated: 2024/02/10 02:27:55 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	model(void *void_cub)
{
	// printf("model\n");
	t_cub *cub;
	
	cub = (t_cub *)void_cub;
	
	if (cub->controller.game_over)
	{
		exit_game(cub);
		return(0);
	}
	// calculate everything realted to the model
	// DONT CALCULATE THE WALL LINE HEIGT FOR EACH COLUMN, DO IT IN THE VIEW
	
	//all the math, the raycasting (including DDA)
	// for minimap and 2d map there are not really calculations to do
	// so they are not part of the model and the images/frames will be created
	// in the view
	// if (cub->controller.move_up == true)
	// 	printf("model key up");

	// // triggering the view to update the images based on the changes from
	// // the model
	if (cub->controller.move_forward || cub->controller.move_backwards || cub->controller.move_left || cub->controller.move_right)
		player_move(&cub->player, &cub->controller, &cub->map_config);

	if (cub->controller.rotate_right)
		player_rotate(&cub->player, true);
	else if (cub->controller.rotate_left)
		player_rotate(&cub->player, false);
	update_v_plane(&cub->player);
	update_map3d(&cub->map3d, &cub->player, &cub->map_config);

	view(cub);
	
	return(0);
}






















//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------





// static void   equip_mini_img(t_cub *cub)
// {
// 	// calculate the current view and draw it to the img
// 	int	y;
// 	int x;
	
// 	// TODO: change to create the frame using "put_wall" from minimap.c
// 	y = 0;
// 	ft_putstr_fd("Map:\n", STDOUT_FILENO);
// 	while (cub->map[y])
// 	{
// 		x = 0;
// 		while (cub->map[y][x])
// 		{
// 			if(x == (int)(cub->player.pos_x / TILE_SIZE) && y == (int)(cub->player.pos_y / TILE_SIZE))
// 			{
// 				if (cub->player.rot_angle == 0)
// 					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_N.mlx_img, x*MINIMAP_PIXEL_WIDTH, y*MINIMAP_PIXEL_WIDTH);	
// 				else if (cub->player.rot_angle == 90)
// 					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_E.mlx_img, x*MINIMAP_PIXEL_WIDTH, y*MINIMAP_PIXEL_WIDTH);	
// 				else if (cub->player.rot_angle == 180)
// 					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_S.mlx_img, x*MINIMAP_PIXEL_WIDTH, y*MINIMAP_PIXEL_WIDTH);	
// 				else if (cub->player.rot_angle == 270)
// 					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_W.mlx_img, x*MINIMAP_PIXEL_WIDTH, y*MINIMAP_PIXEL_WIDTH);	

// 			}
// 			else if (cub->map[y][x] == '1')
// 				mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.wall.mlx_img, x*MINIMAP_PIXEL_WIDTH, y*MINIMAP_PIXEL_WIDTH);	
// 			else if (cub->map[y][x] == '0')
// 				mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.empty.mlx_img, x*MINIMAP_PIXEL_WIDTH, y*MINIMAP_PIXEL_WIDTH);	
// 			x++;
// 		}
// 		y++;
// 	}
	
// }

// void update_model(t_cub *cub)
// {
// 	angleToVector(cub->player.rot_angle, &cub->ray.v_direction);
// 	// printf("v_direction: %f, %f\n", cub->ray.v_direction.x, cub->ray.v_direction.y);
// 	minimap_main(cub);
	
// 	// dbg_put_player(cub);
// 	// dbg_put_minimap_big(cub);	
// 	// dbg_put_minimap_small(cub);
	
// 	create_frame(cub);
// 	calculate_rays(cub);
// }
