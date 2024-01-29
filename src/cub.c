/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:15:01 by astein            #+#    #+#             */
/*   Updated: 2024/01/29 19:01:45 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	cub->map = NULL;
}

void	free_cub(t_cub *cub)
{
	(void)cub;
	// TODO:
}
