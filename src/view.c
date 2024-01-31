/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:26:53 by astein            #+#    #+#             */
/*   Updated: 2024/01/30 13:03:46 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_win(t_cub *cub)
{
	cub->win.mlx = mlx_init();
	//mlx_get_screen_size(mod->mlx, &screen_width, &screen_height);
	cub->win.win_width = WIN_WIDTH;
	cub->win.win_height = WIN_HEIGHT;
	cub->win.win = mlx_new_window(cub->win.mlx, cub->win.win_width, cub->win.win_height,
			"cub3D");
}

void	update_view(t_cub *cub)
{
	//put raycast to window
	//mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->img_ray.mlx_img, 0, 0);
	
	//put minimap to wind.
	// if (cub->show_mini)
		// mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->img_mini.mlx_img, 50, 50);
}
