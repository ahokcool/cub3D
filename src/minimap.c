/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:19:58 by astein            #+#    #+#             */
/*   Updated: 2024/01/31 18:18:18 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall(t_cub *cub, int x, int y)
{
	// copy the wall from the image to the minimap frame of minimap at postion x y
	// the frame is here
	// cub->minimap.img_mini.mlx_img;
	
	// the wall image is here
	// cub->minimap.wall.mlx_img
}

void	ini_minimap(t_cub *cub)
{
	cub->minimap.wall.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/wall.xpm", &cub->minimap.wall.width, &cub->minimap.wall.height);
	cub->minimap.empty.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/floor.xpm", &cub->minimap.empty.width, &cub->minimap.empty.height);
	cub->minimap.player_N.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_N.xpm", &cub->minimap.player_N.width, &cub->minimap.player_N.height);
	cub->minimap.player_E.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_E.xpm", &cub->minimap.player_E.width, &cub->minimap.player_E.height);
	cub->minimap.player_S.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_S.xpm", &cub->minimap.player_S.width, &cub->minimap.player_S.height);
	cub->minimap.player_W.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_W.xpm", &cub->minimap.player_W.width, &cub->minimap.player_W.height);
}