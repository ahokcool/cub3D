/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:40:53 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 17:58:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->v_plane.x = 0;
	player->v_plane.y = 0;
	player->fov = -1;
	ini_img(&player->player_NE);
	ini_img(&player->player_NW);
	ini_img(&player->player_SE);
	ini_img(&player->player_SW);
	ini_img(&player->player_N);
	ini_img(&player->player_S);
	ini_img(&player->player_E);
	ini_img(&player->player_W);
}

static	void config_player_start_pos(t_map_file *map_file, t_player *player)
{
	t_vector_int	cur_tile;
	
	cur_tile.y = 0;
	while (map_file->map[cur_tile.y])
	{
		cur_tile.x = 0;
		while (map_file->map[cur_tile.y][cur_tile.x])
		{
			if (map_file->map[cur_tile.y][cur_tile.x] == 'N' || map_file->map[cur_tile.y][cur_tile.x] == 'S' || map_file->map[cur_tile.y][cur_tile.x] == 'E' || map_file->map[cur_tile.y][cur_tile.x] == 'W')
			{
				if (map_file->map[cur_tile.y][cur_tile.x] == 'N')
					player->dir.y = -1;
				else if (map_file->map[cur_tile.y][cur_tile.x] == 'E')
					player->dir.x = 1;
				else if (map_file->map[cur_tile.y][cur_tile.x] == 'S')
					player->dir.y = 1;
				else if (map_file->map[cur_tile.y][cur_tile.x] == 'W')
					player->dir.x = -1;
				map_file->map[cur_tile.y][cur_tile.x] = '0';
				player->pos.x = cur_tile.x + 0.5;	//To put player in middle of the tile
				player->pos.y = cur_tile.y + 0.5;	//To put player in middle of the tile
				break ;
			}
			cur_tile.x++;
		}
		cur_tile.y++;
	}
	// dbg_put_player(player);
}

void	update_v_plane(t_player *player)
{
	t_vector_dbl	plane;
	
	plane.x = player->dir.x;
	plane.y = player->dir.y;
	rotate_vector_dbl(&plane, 90);
	player->v_plane.x = plane.x * (player->fov/100);
	player->v_plane.y = plane.y * (player->fov/100);
}

void config_player(t_cub *cub, t_map_file *map_file, t_player *player)
{
	player->fov = 100.00;
	printf("FOV: %f\n", cub->player.fov);
	config_img_file(cub, &player->player_NE, "./textures/minimap/player_NE.xpm");
	config_img_file(cub, &player->player_NW, "./textures/minimap/player_NW.xpm");
	config_img_file(cub, &player->player_SE, "./textures/minimap/player_SE.xpm");
	config_img_file(cub, &player->player_SW, "./textures/minimap/player_SW.xpm");
	config_img_file(cub, &player->player_N, "./textures/minimap/player_N.xpm");
	config_img_file(cub, &player->player_S, "./textures/minimap/player_S.xpm");
	config_img_file(cub, &player->player_E, "./textures/minimap/player_E.xpm");
	config_img_file(cub, &player->player_W, "./textures/minimap/player_W.xpm");
	config_player_start_pos(map_file, player);
	update_v_plane(player);
}

void	destroy_player(void *mlx_ptr, t_player *player)
{
	destroy_img(mlx_ptr, player->player_NE.mlx_img);
	destroy_img(mlx_ptr, player->player_NW.mlx_img);
	destroy_img(mlx_ptr, player->player_SE.mlx_img);
	destroy_img(mlx_ptr, player->player_SW.mlx_img);
	destroy_img(mlx_ptr, player->player_N.mlx_img);
	destroy_img(mlx_ptr, player->player_S.mlx_img);
	destroy_img(mlx_ptr, player->player_E.mlx_img);
	destroy_img(mlx_ptr, player->player_W.mlx_img);

}

void 	player_rotate(t_player *player, bool turn_right)
{

	if (turn_right)
		rotate_vector_dbl(&player->dir, ROT_SPEED);
	else
		rotate_vector_dbl(&player->dir, -ROT_SPEED);
	normalize_vector_dbl(&player->dir);

	// update_v_plane(player);
	
	// dbg_put_player(player);
}

void 	player_move(t_player *player, t_controller *controller, t_map_file *map_file)
{
	t_vector_dbl	dir;
	t_vector_dbl	colission;
	
	dir.x = 0;
	dir.y = 0;
	if (controller->move_forward)
		dir.y -= 1;
	if (controller->move_backwards)
		dir.y += 1;
	if (controller->move_left)
		dir.x -= 1;
	if (controller->move_right)
		dir.x += 1;
	rotate_vector_by_vector(&dir, &player->dir);
	normalize_vector_dbl(&dir);
	dir.x *= MOVE_SPEED;
	dir.y *= MOVE_SPEED;
	
	colission.x = 0;
	colission.y = 0;
	if (dir.x > 0)
		colission.x = 0.1;
	else if (dir.x < 0)
		colission.x = -0.1;
	if (dir.y > 0)
		colission.y = 0.1;
	else if (dir.y < 0)
		colission.y = -0.1;

	// normalize_vector_dbl(&dir);
	
	// Coalision detection
	// && (map_file->map[(int)(player->pos.y)][(int)(player->pos.x + (dir.x) - 0.1)] == '0'))
	if (map_file->map[(int)(player->pos.y)][(int)(player->pos.x + (dir.x) + colission.x)] == '0')
		player->pos.x += dir.x;
	// && (map_file->map[(int)(player->pos.y + (dir.y))][(int)(player->pos.x - 0.1)] == '0'))
	if (map_file->map[(int)(player->pos.y + (dir.y)  + colission.y)][(int)(player->pos.x)] == '0')
		player->pos.y += dir.y;
	
	// update_v_plane(player);
	// dbg_put_player(player);
}
