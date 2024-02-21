/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:15:01 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 21:47:35 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// printf("ini_cub\n");
static void	ini_cub(t_cub *cub)
{
	cub->running = false;
	ini_win(&cub->win);
	ini_img(&cub->img_2d);
	ini_map(cub);
	ini_player(&cub->player);
	ini_map2d(&cub->map2d);
	ini_map3d(&cub->map3d);
	ini_controller(&cub->controller);
}

	// printf("config_cub\n");
static	bool	config_cub(t_cub *cub, char *map_path)
{
	if (!config_map(cub, map_path))
		return (false);
	config_win(&cub->win);
	config_img_dim(cub, &cub->img_2d, NULL);
	config_img_dim(cub, &cub->img_3d, NULL);
	config_player(&cub->map_file, &cub->player);
	config_map2d(cub, &cub->map2d);
	config_map3d(cub, &cub->map3d, &cub->player);
	return (true);
}

bool	ready_cub(t_cub *cub, char *map_path)
{
	ini_cub(cub);
	if (!config_cub(cub, map_path))
		return (false);
	view(cub);
	cub->running = true;
	return (true);
}

int	destroy_cub(t_cub *cub)
{
	destroy_img(cub->win.mlx, &cub->img_2d);
	destroy_img(cub->win.mlx, &cub->img_3d);
	destroy_map(&cub->map_file);
	destroy_map2d(cub->win.mlx, &cub->map2d);
	destroy_map3d(cub->win.mlx, &cub->map3d);
	destroy_win(&cub->win);
	exit (0);
	return (0);
}
