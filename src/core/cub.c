/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:15:01 by astein            #+#    #+#             */
/*   Updated: 2024/02/20 17:36:25 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ini_cub(t_cub *cub)
{
	printf("ini_cub\n");
	cub->running = false;
	
	ini_win(&cub->win);
	ini_img(&cub->img_2d);
	ini_map(cub);
	ini_player(&cub->player);
	ini_map2d(&cub->map2d);
	ini_map3d(&cub->map3d);
	ini_minimap(&cub->minimap);
	// ini_ray(cub->ray);
	ini_controller(&cub->controller);	
}

static	bool	config_cub(t_cub *cub, char *map_path)
{
	printf("config_cub\n");
	if (!config_map(cub, map_path))
		return (false);
	config_win(&cub->win);
	config_img_dim(cub, &cub->img_2d, NULL);
	config_img_dim(cub, &cub->img_3d, NULL);
	config_img_dim(cub, &cub->img_mini, NULL);
	config_player(cub, &cub->map_file, &cub->player);
	config_map2d(cub, &cub->map2d);
	config_map3d(cub, &cub->map3d, &cub->player);
	config_minimap(cub, &cub->minimap, cub->map_file.map);
	return(true);
	// config_ray(cub->ray);
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

void	destroy_cub(t_cub *cub)
{
	// TODO: copy the function names from ini and adjust them to free all the shit
	destroy_img(cub->win.mlx, &cub->img_2d);
	destroy_img(cub->win.mlx, &cub->img_mini);
	destroy_img(cub->win.mlx, &cub->img_3d);
	destroy_map(&cub->map_file);
	destroy_player(cub->win.mlx, &cub->player);
	destroy_map2d(cub->win.mlx, &cub->map2d);
	destroy_map3d(cub->win.mlx, &cub->map3d);
	destroy_minimap(cub->win.mlx, &cub->minimap);
	// free_ray(cub->ray);
	destroy_win(&cub->win);
	exit(0);
}
