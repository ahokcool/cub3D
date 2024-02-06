/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:15:01 by astein            #+#    #+#             */
/*   Updated: 2024/02/06 22:02:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub
cub = ini_main();	
	config_main();

void	ini_cub(t_cub *cub)
{
	ini_win(cub->win);
	ini_img(cub); //RAY MINI & 2D
	ini_map(cub->map_config);
	ini_player(cub->player);
	ini_map2d(cub->map2d);
	ini_minimap(cub->minimap);
	ini_ray(cub->ray);
	ini_controller(cub->controller);
	cub->show_mini = false;
	cub->show_map2d = false;
	
	//TODO: create all the ini functions in the responsible .c files 
	//and move the code above there
	//also make sure that ini and config a strictly seperated!
	cub->win.mlx = NULL;
	cub->win.win = NULL;
	cub->win.win_height = 0;
	cub->win.win_width = 0;
	cub->img_ray.mlx_img = NULL;
	cub->img_ray.addr = NULL;
	cub->img_ray.bpp = 0;
	cub->img_ray.line_len = 0;
	cub->img_ray.endian = 0;
	cub->img_mini.mlx_img = NULL;
	cub->img_mini.addr = NULL;
	cub->img_mini.bpp = 0;
	cub->img_mini.line_len = 0;
	cub->img_mini.endian = 0;
}

void	config_cub(t_cub *cub)
{
	config_win(cub->win);
	config_img(cub); //RAY MINI & 2D
	config_map(cub->map_config);
	config_player(cub->player);
	config_map2d(cub->map2d);
	config_minimap(cub->minimap);
	config_ray(cub->ray);
	config_controller(cub->controller);
}


void	free_cub(t_cub *cub)
{
	(void)cub;
	// TODO: copy the function names from ini and adjust them to free all the shit
	free_win(cub->win);
	free_img(cub); //RAY MINI & 2D
	free_map(cub->map_config);
	free_player(cub->player);
	free_map2d(cub->map2d);
	free_minimap(cub->minimap);
	free_ray(cub->ray);
	free_controller(cub->controller);
}
