/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:15:01 by astein            #+#    #+#             */
/*   Updated: 2024/02/19 16:13:07 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_cub *cub)
{
	cub->map_file.no_texture = NULL;
	cub->map_file.so_texture = NULL;
	cub->map_file.we_texture = NULL;
	cub->map_file.ea_texture = NULL;
	cub->map_file.floor_clr.red = (uint8_t)260;
	cub->map_file.ceiling_clr.red = (uint8_t)260;
	cub->map_file.map = NULL;
}

void	free_map(t_cub *cub)
{
	if (cub->map_file.no_texture)
		free (cub->map_file.no_texture);
	if (cub->map_file.so_texture)
		free (cub->map_file.so_texture);
	if (cub->map_file.we_texture)
		free (cub->map_file.we_texture);
	if (cub->map_file.ea_texture)
		free (cub->map_file.ea_texture);
	if (cub->map_file.map)
		free_whatever("m", cub->map_file.map);
}

void	init_cub(t_cub *cub)
{
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
	init_map(cub);
}

void	free_cub(t_cub *cub)
{
	(void)cub;
	// TODO:
}
