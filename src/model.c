/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:26:36 by astein            #+#    #+#             */
/*   Updated: 2024/01/30 15:16:55 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void   equip_ray_img(t_cub *cub)
{
	(void)cub;
	// calculate the current view and draw it to the img
}

static void   equip_mini_img(t_cub *cub)
{
	// calculate the current view and draw it to the img
	int	i;
	int j;
	
	i = 0;
	ft_putstr_fd("Map:\n", STDOUT_FILENO);
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if(j == cub->player.pos_x && i == cub->player.pos_y)
			{
				if (cub->player.rot_angle == 0)
					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_E.mlx_img, j*MINIMAP_PIXEL_WIDTH, i*MINIMAP_PIXEL_WIDTH);	
				else if (cub->player.rot_angle == 90)
					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_N.mlx_img, j*MINIMAP_PIXEL_WIDTH, i*MINIMAP_PIXEL_WIDTH);	
				else if (cub->player.rot_angle == 180)
					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_W.mlx_img, j*MINIMAP_PIXEL_WIDTH, i*MINIMAP_PIXEL_WIDTH);	
				else if (cub->player.rot_angle == 270)
					mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.player_S.mlx_img, j*MINIMAP_PIXEL_WIDTH, i*MINIMAP_PIXEL_WIDTH);	

			}
			else if (cub->map[i][j] == '1')
				mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.wall.mlx_img, j*MINIMAP_PIXEL_WIDTH, i*MINIMAP_PIXEL_WIDTH);	
			else if (cub->map[i][j] == '0')
				mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->minimap.empty.mlx_img, j*MINIMAP_PIXEL_WIDTH, i*MINIMAP_PIXEL_WIDTH);	
			j++;
		}
		i++;
	}
	
}

void eqip_imgs(t_cub *cub)
{
	mlx_clear_window(cub->win.mlx, cub->win.win);
	equip_ray_img(cub);
	if(cub->show_mini)
		equip_mini_img(cub);
	update_view(cub);
	dbg_put_player(cub);
	dbg_put_minimap(cub);
}