/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:40:53 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 22:15:40 by astein           ###   ########.fr       */
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
}

static bool	check_for_player(t_map_file *map_file, t_player *player,
	t_vector_int cur_tile)
{
	if (map_file->map[cur_tile.y][cur_tile.x] == 'N')
		player->dir.y = -1;
	else if (map_file->map[cur_tile.y][cur_tile.x] == 'E')
		player->dir.x = 1;
	else if (map_file->map[cur_tile.y][cur_tile.x] == 'S')
		player->dir.y = 1;
	else if (map_file->map[cur_tile.y][cur_tile.x] == 'W')
		player->dir.x = -1;
	else
		return (false);
	return (true);
}

static void	config_player_start_pos(t_map_file *map_file, t_player *player)
{
	t_vector_int	cur_tile;

	cur_tile.y = 0;
	while (map_file->map[cur_tile.y])
	{
		cur_tile.x = 0;
		while (map_file->map[cur_tile.y][cur_tile.x])
		{
			if (check_for_player(map_file, player, cur_tile))
			{
				map_file->map[cur_tile.y][cur_tile.x] = '0';
				player->pos.x = cur_tile.x + 0.5;
				player->pos.y = cur_tile.y + 0.5;
				break ;
			}
			cur_tile.x++;
		}
		cur_tile.y++;
	}
}

void	config_player(t_map_file *map_file, t_player *player)
{
	player->fov = 100.00;
	config_player_start_pos(map_file, player);
	update_v_plane(player);
}
