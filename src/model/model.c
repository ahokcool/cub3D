/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:26:36 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 17:54:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	model(void *void_cub)
{
	t_cub	*cub;

	// printf("model\n");
	cub = (t_cub *)void_cub;
	if (cub->controller.game_over)
	{
		exit_game(cub);
		return (0);
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
	if (cub->controller.move_forward || cub->controller.move_backwards
		|| cub->controller.move_left || cub->controller.move_right)
		player_move(&cub->player, &cub->controller, &cub->map_file);
	if (cub->controller.rotate_right)
		player_rotate(&cub->player, true);
	else if (cub->controller.rotate_left)
		player_rotate(&cub->player, false);
	update_v_plane(&cub->player);
	update_map3d(&cub->map3d, &cub->player, &cub->map_file);
	view(cub);
	return (0);
}

