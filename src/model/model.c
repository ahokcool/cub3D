/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:26:36 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 19:10:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	model(void *void_cub)
{
	t_cub	*cub;

	cub = (t_cub *)void_cub;
	if (cub->controller.game_over)
	{
		exit_game(cub);
		return (0);
	}
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
