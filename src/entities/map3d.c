/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:52:12 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 20:55:44 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map3d(t_map3d *map3d)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		ini_col(&map3d->cols[i]);
	ini_img(&map3d->img_wall_no);
	ini_img(&map3d->img_wall_ea);
	ini_img(&map3d->img_wall_so);
	ini_img(&map3d->img_wall_we);
}

void	config_map3d(t_cub *cub, t_map3d *map3d, t_player *player)
{
	(void)map3d;
	(void)player;
	config_img_file(cub, &map3d->img_wall_no, cub->map_file.no_texture);
	config_img_file(cub, &map3d->img_wall_ea, cub->map_file.ea_texture);
	config_img_file(cub, &map3d->img_wall_so, cub->map_file.so_texture);
	config_img_file(cub, &map3d->img_wall_we, cub->map_file.we_texture);
}

void	destroy_map3d(void *mlx, t_map3d *map3d)
{
	destroy_img(mlx, &map3d->img_wall_no);
	destroy_img(mlx, &map3d->img_wall_we);
	destroy_img(mlx, &map3d->img_wall_so);
	destroy_img(mlx, &map3d->img_wall_ea);
}
