/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:40:53 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 20:15:53 by astein           ###   ########.fr       */
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
	ini_img(&player->player_NE);
	ini_img(&player->player_NW);
	ini_img(&player->player_SE);
	ini_img(&player->player_SW);
	ini_img(&player->player_N);
	ini_img(&player->player_S);
	ini_img(&player->player_E);
	ini_img(&player->player_W);
}

static	void config_player_start_pos(t_map_config *map_config, t_player *player)
{
	t_vector_int	cur_tile;
	
	cur_tile.y = 0;
	while (map_config->map[cur_tile.y])
	{
		cur_tile.x = 0;
		while (map_config->map[cur_tile.y][cur_tile.x])
		{
			if (map_config->map[cur_tile.y][cur_tile.x] == 'N' || map_config->map[cur_tile.y][cur_tile.x] == 'S' || map_config->map[cur_tile.y][cur_tile.x] == 'E' || map_config->map[cur_tile.y][cur_tile.x] == 'W')
			{
				if (map_config->map[cur_tile.y][cur_tile.x] == 'N')
					player->dir.y = -1;
				else if (map_config->map[cur_tile.y][cur_tile.x] == 'E')
					player->dir.x = 1;
				else if (map_config->map[cur_tile.y][cur_tile.x] == 'S')
					player->dir.y = 1;
				else if (map_config->map[cur_tile.y][cur_tile.x] == 'W')
					player->dir.x = -1;
				map_config->map[cur_tile.y][cur_tile.x] = '0';
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

void config_player(t_cub *cub, t_map_config *map_config, t_player *player)
{

	config_img_file(cub, &player->player_NE, "./textures/minimap/player_NE.xpm");
	config_img_file(cub, &player->player_NW, "./textures/minimap/player_NW.xpm");
	config_img_file(cub, &player->player_SE, "./textures/minimap/player_SE.xpm");
	config_img_file(cub, &player->player_SW, "./textures/minimap/player_SW.xpm");
	config_img_file(cub, &player->player_N, "./textures/minimap/player_N.xpm");
	config_img_file(cub, &player->player_S, "./textures/minimap/player_S.xpm");
	config_img_file(cub, &player->player_E, "./textures/minimap/player_E.xpm");
	config_img_file(cub, &player->player_W, "./textures/minimap/player_W.xpm");
	config_player_start_pos(map_config, player);
	t_vector_dbl	plane;

	plane.x = player->dir.x;
	plane.y = player->dir.y;
	rotate_vector_dbl(&plane, 90);
	player->v_plane.x = plane.x;
	player->v_plane.y = plane.y;
	normalize_vector_dbl(&player->v_plane);
}

void	destroy_player(void *mlx, t_player *player)
{
	destroy_img(mlx, player->player_NE.mlx_img);
	destroy_img(mlx, player->player_NW.mlx_img);
	destroy_img(mlx, player->player_SE.mlx_img);
	destroy_img(mlx, player->player_SW.mlx_img);
	destroy_img(mlx, player->player_N.mlx_img);
	destroy_img(mlx, player->player_S.mlx_img);
	destroy_img(mlx, player->player_E.mlx_img);
	destroy_img(mlx, player->player_W.mlx_img);

}

void 	player_rotate(t_player *player, bool turn_right)
{
	t_vector_dbl	plane;

	if (turn_right)
		rotate_vector_dbl(&player->dir, ROT_SPEED);
	else
		rotate_vector_dbl(&player->dir, -ROT_SPEED);
	normalize_vector_dbl(&player->dir);

	plane.x = player->dir.x;
	plane.y = player->dir.y;
	rotate_vector_dbl(&plane, 90);
	player->v_plane.x = plane.x;
	player->v_plane.y = plane.y;
	normalize_vector_dbl(&player->v_plane);
	// dbg_put_player(player);
}

void 	player_move(t_player *player, t_controller *controller, t_map_config *map_config)
{
	t_vector_dbl	dir;
	
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
	
	// Coalision detection
	if (map_config->map[(int)(player->pos.y)][(int)(player->pos.x + (dir.x))] == '0')
		player->pos.x += dir.x;
	if (map_config->map[(int)(player->pos.y + (dir.y))][(int)(player->pos.x)] == '0')
		player->pos.y += dir.y;
	
	// dbg_put_player(player);
}














//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



int	get_player_pos(t_cub *cub, char format)
{
	if (format == 'x')
		return (cub->player.pos.x);
	else if (format == 'y')
		return (cub->player.pos.y);
	else
		return (0);
}



// void player_move(t_cub *cub, char direction)
// {
// 	(void)cub;
// 	(void)direction;
// 	// Walking vectors for U, D, L, R
//     // double walk_vectors[4][2] = {
//     //     {0, -1},  // U - forward
//     //     {0, 1}, // D - backward
//     //     {-1, 0}, // L - left
//     //     {1, 0}   // R - right
//     // };

//     // int dir_index;
//     // if (direction == 'U') dir_index = 0;
//     // else if (direction == 'D') dir_index = 1;
//     // else if (direction == 'L') dir_index = 2;
//     // else if (direction == 'R') dir_index = 3;


// 	// TODO: DOESNT WORK SINCE WE NOW USE VECTORS
//     // // Convert rotation angle to radians
//     // double rad = cub->player.rot_angle * (M_PI / 180.0); 

//     // // Calculate the rotated walking vector
//     // double walk_x = walk_vectors[dir_index][0] * cos(rad) - walk_vectors[dir_index][1] * sin(rad);
//     // double walk_y = walk_vectors[dir_index][0] * sin(rad) + walk_vectors[dir_index][1] * cos(rad);
// 	// // TODO: check if the player is walking into a wall
// 	// cub->player.pos_x += (walk_x / TILE_SIZE);
// 	// cub->player.pos_y += (walk_y / TILE_SIZE);
// }