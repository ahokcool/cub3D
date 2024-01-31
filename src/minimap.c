/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:19:58 by astein            #+#    #+#             */
/*   Updated: 2024/01/30 13:18:13 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_minimap(t_cub *cub)
{
	cub->minimap.wall.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/wall.xpm", &cub->minimap.wall.width, &cub->minimap.wall.height);
	cub->minimap.empty.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/floor.xpm", &cub->minimap.empty.width, &cub->minimap.empty.height);
	cub->minimap.player_N.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_N.xpm", &cub->minimap.player_N.width, &cub->minimap.player_N.height);
	cub->minimap.player_E.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_E.xpm", &cub->minimap.player_E.width, &cub->minimap.player_E.height);
	cub->minimap.player_S.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_S.xpm", &cub->minimap.player_S.width, &cub->minimap.player_S.height);
	cub->minimap.player_W.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_W.xpm", &cub->minimap.player_W.width, &cub->minimap.player_W.height);
}