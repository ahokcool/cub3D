/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:42:25 by astein            #+#    #+#             */
/*   Updated: 2024/02/19 19:35:10 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map2d(t_map2d *map2d)
{
	map2d->map_2d = NULL;
	ini_img(&map2d->img_wall);
	ini_img(&map2d->img_floor);
}
void	config_map2d(t_cub *cub, t_map2d *map2d)
{
	map2d->map_2d = cub->map_file.map; //TODO: copy the map if the parser changes it
	config_img_file(cub, &map2d->img_wall, "./textures/map2d/wall.xpm");
	config_img_file(cub, &map2d->img_floor, "./textures/map2d/floor.xpm");
}

void	destroy_map2d(void *mlx, t_map2d *map2d)
{
	mlx_destroy_image(mlx, map2d->img_wall.mlx_img);
	mlx_destroy_image(mlx, map2d->img_floor.mlx_img);
	free_whatever("m", map2d->map_2d);
}

void	 draw_rays_2d(t_cub *cub)
{
	t_vector_dbl	player_cord;
	t_vector_dbl	hit_pos;

	player_cord.x = cub->player.pos.x * MAP2D_PIXEL_WIDTH;
	player_cord.y = cub->player.pos.y * MAP2D_PIXEL_WIDTH;
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
	{
		hit_pos.x = cub->map3d.columns[i].hit_pos.x * MAP2D_PIXEL_WIDTH - player_cord.x;
		hit_pos.y = cub->map3d.columns[i].hit_pos.y * MAP2D_PIXEL_WIDTH - player_cord.y;
		draw_line(&cub->img_2d, &player_cord, &hit_pos, 0xFFFFFF);
	}
}

void	draw_rays_hits(t_cub *cub)
{
	// (void)cub;
	t_vector_dbl	hit_pos;
	
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
	{
		hit_pos.x = cub->map3d.columns[i].hit_pos.x * MAP2D_PIXEL_WIDTH;
		hit_pos.y = cub->map3d.columns[i].hit_pos.y * MAP2D_PIXEL_WIDTH;
		
		// if (cub->map3d.columns[i].hit_direction == 'S')
		// 	hit_cord.x += (double)MAP2D_PIXEL_WIDTH;
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
	
	// So that the line is longer displayed:
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

	cur_tile.x = 0;
	cur_tile.y = 0;

	//DRAW MAP2D
	while (cub->map2d.map_2d[cur_tile.y])
	{
		cur_tile.x = 0;
		while (cub->map2d.map_2d[cur_tile.y][cur_tile.x])
		{
			if (cub->map2d.map_2d[cur_tile.y][cur_tile.x] == '1')
				put_tile(cub, cur_tile.x * MAP2D_PIXEL_WIDTH, cur_tile.y * MAP2D_PIXEL_WIDTH, &cub->map2d.img_wall, &cub->img_2d, 0);
			else if (cub->map2d.map_2d[cur_tile.y][cur_tile.x] == '0')
				put_tile(cub, cur_tile.x * MAP2D_PIXEL_WIDTH, cur_tile.y * MAP2D_PIXEL_WIDTH, &cub->map2d.img_floor, &cub->img_2d, 0);
			cur_tile.x++;
		}
		cur_tile.y++;
	}
	draw_player(cub);
}
