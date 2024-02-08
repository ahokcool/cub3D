/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:15:01 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 16:31:03 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ini_cub(t_cub *cub)
{
	printf("ini_cub\n");
	cub->running = false;
	cub->show_mini = false;
	cub->show_map2d = true;
	ini_win(&cub->win);
	ini_img(&cub->img_2d);
	ini_img(&cub->img_3d);
	ini_img(&cub->img_mini);
	ini_map(&cub->map_config);
	ini_player(&cub->player);
	ini_map2d(&cub->map2d);
	ini_map3d(&cub->map3d);
	ini_minimap(&cub->minimap);
	// ini_ray(cub->ray);
	ini_controller(&cub->win.mlx, &cub->controller);	
}

static	void	config_cub(t_cub *cub, char *map_path)
{
	printf("config_cub\n");
	config_win(&cub->win);
	config_img_dim(cub, &cub->img_2d, NULL);
	config_img_dim(cub, &cub->img_3d, NULL);
	config_img_dim(cub, &cub->img_mini, NULL);
	config_map(&cub->map_config, map_path);
	config_player(cub, &cub->map_config, &cub->player);
	config_map2d(cub, &cub->map2d);
	config_map3d(&cub->map3d, &cub->player);
	config_minimap(cub, &cub->minimap, cub->map_config.map);
	// config_ray(cub->ray);
}
bool	ready_cub(t_cub *cub, char *map_path)
{
	ini_cub(cub);
	config_cub(cub, map_path);
	view(cub);
	cub->running = true;
	return (true); //TODO: FALSE IF FAILS
}

void	destroy_cub(t_cub *cub)
{
	// TODO: copy the function names from ini and adjust them to free all the shit
	destroy_img(&cub->win.mlx, &cub->img_2d);
	destroy_img(&cub->win.mlx, &cub->img_mini);
	destroy_img(&cub->win.mlx, &cub->img_3d);
	destroy_map(&cub->map_config);
	destroy_player(&cub->win.mlx, &cub->player);
	destroy_map2d(&cub->win.mlx, &cub->map2d);
	destroy_minimap(&cub->win.mlx, &cub->minimap);
	// free_ray(cub->ray);
	destroy_win(&cub->win);
	exit(0);
}
