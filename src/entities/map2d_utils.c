/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:00:35 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 19:03:24 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_rays_2d(t_cub *cub)
{
	t_vector_dbl	player_cord;
	t_vector_dbl	hit_pos;
	int				i;

	player_cord.x = cub->player.pos.x * MAP2D_PIXEL_WIDTH;
	player_cord.y = cub->player.pos.y * MAP2D_PIXEL_WIDTH;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		hit_pos.x = cub->map3d.columns[i].hit_pos.x * MAP2D_PIXEL_WIDTH
			- player_cord.x;
		hit_pos.y = cub->map3d.columns[i].hit_pos.y * MAP2D_PIXEL_WIDTH
			- player_cord.y;
		draw_line(&cub->img_2d, &player_cord, &hit_pos, 0xD2D2D2);
	}
}

static void	draw_rays_hits(t_cub *cub)
{
	t_vector_dbl	hit_pos;
	int				i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		hit_pos.x = cub->map3d.columns[i].hit_pos.x * MAP2D_PIXEL_WIDTH;
		hit_pos.y = cub->map3d.columns[i].hit_pos.y * MAP2D_PIXEL_WIDTH;
		if (cub->map3d.columns[i].hit_direction == 'N')
			set_pixel_to_image(&cub->img_2d, hit_pos.x, hit_pos.y, CLR_NORTH);
		if (cub->map3d.columns[i].hit_direction == 'E')
			set_pixel_to_image(&cub->img_2d, hit_pos.x, hit_pos.y, CLR_EAST);
		if (cub->map3d.columns[i].hit_direction == 'S')
			set_pixel_to_image(&cub->img_2d, hit_pos.x, hit_pos.y, CLR_SOUTH);
		if (cub->map3d.columns[i].hit_direction == 'W')
			set_pixel_to_image(&cub->img_2d, hit_pos.x, hit_pos.y, CLR_WEST);
	}
}

static void	draw_player(t_cub *cub)
{
	t_vector_dbl	player_cord;
	t_vector_dbl	player_vec;
	t_vector_dbl	plane_cord;
	t_vector_dbl	plane_vec;
	t_vector_dbl	plane_vec_neg;

	player_cord.x = cub->player.pos.x * MAP2D_PIXEL_WIDTH;
	player_cord.y = cub->player.pos.y * MAP2D_PIXEL_WIDTH;
	player_vec.x = cub->player.dir.x * 10;
	player_vec.y = cub->player.dir.y * 10;
	plane_cord.x = player_cord.x + player_vec.x;
	plane_cord.y = player_cord.y + player_vec.y;
	plane_vec.x = cub->player.v_plane.x * 10;
	plane_vec.y = cub->player.v_plane.y * 10;
	plane_vec_neg.x = plane_vec.x;
	plane_vec_neg.y = plane_vec.y;
	rotate_vector_dbl(&plane_vec, 180);
	draw_rays_2d(cub);
	draw_rays_hits(cub);
	draw_line(&cub->img_2d, &player_cord, &player_vec, 0x000000);
	draw_line(&cub->img_2d, &plane_cord, &plane_vec, 0xFF0000);
	draw_line(&cub->img_2d, &plane_cord, &plane_vec_neg, 0xFF0000);
}

void	update_map2d_frame(t_cub *cub)
{
	t_vector_int	cur_tile;
	t_vector_int	pos;

	cur_tile.x = 0;
	cur_tile.y = 0;
	while (cub->map2d.map_2d[cur_tile.y])
	{
		cur_tile.x = 0;
		while (cub->map2d.map_2d[cur_tile.y][cur_tile.x])
		{
			pos.x = cur_tile.x * MAP2D_PIXEL_WIDTH;
			pos.y = cur_tile.y * MAP2D_PIXEL_WIDTH;
			if (cub->map2d.map_2d[cur_tile.y][cur_tile.x] == '1')
				put_tile(pos, &cub->map2d.img_wall, &cub->img_2d);
			else if (cub->map2d.map_2d[cur_tile.y][cur_tile.x] == '0')
				put_tile(pos, &cub->map2d.img_floor, &cub->img_2d);
			cur_tile.x++;
		}
		cur_tile.y++;
	}
	draw_player(cub);
}
