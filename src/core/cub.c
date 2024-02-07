/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:15:01 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 10:59:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ini_cub(t_cub *cub)
{
	cub->show_mini = false;
	cub->show_map2d = false;
	ini_win(&cub->win);
	ini_img(&cub->img_2d);
	ini_img(&cub->img_3d);
	ini_img(&cub->img_mini);
	ini_map(&cub->map_config);
	ini_player(&cub->player);
	ini_map2d(&cub->map2d);
	ini_minimap(&cub->minimap);
	// ini_ray(cub->ray);
	ini_controller(&cub->controller);	
}

static	void	config_cub(t_cub *cub, char *map_path)
{
	config_win(&cub->win);
	config_img(&cub->win.mlx, &cub->img_2d, NULL, NULL);
	config_img(&cub->win.mlx, &cub->img_3d, NULL, NULL);
	config_img(&cub->win.mlx, &cub->img_mini, NULL, NULL); //TODO:
	config_map(&cub->map_config, map_path);
	config_player(&cub->win.mlx, &cub->map_config, &cub->player);
	config_map2d(&cub->win.mlx, &cub->map2d);
	config_minimap(&cub->minimap, &cub->win.mlx, cub->map_config.map);
	// config_ray(cub->ray);
}
void	ready_cub(t_cub *cub, char *map_path)
{
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return ;
	ini_cub(cub);
	config_cub(cub, map_path);
}

void	destroy_cub(t_cub *cub)
{
	(void)cub;
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
}
