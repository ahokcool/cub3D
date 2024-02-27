/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:44:57 by astein            #+#    #+#             */
/*   Updated: 2024/02/27 00:34:30 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_colision_move(t_player *player, t_map_file *map_file,
	t_vector_dbl	dir)
{
	t_vector_dbl	colision;

	colision.x = 0;
	colision.y = 0;
	if (dir.x > 0)
		colision.x = 0.1;
	else if (dir.x < 0)
		colision.x = -0.1;
	if (dir.y > 0)
		colision.y = 0.1;
	else if (dir.y < 0)
		colision.y = -0.1;
	if (map_file->map[(int)(player->pos.y)][(int)(player->pos.x + (dir.x)
			+ colision.x)] == '0')
		player->pos.x += dir.x;
	if (map_file->map[(int)(player->pos.y + (dir.y)
			+ colision.y)][(int)(player->pos.x)] == '0')
		player->pos.y += dir.y;
}

void	player_move(t_player *player, t_controller *controller,
		t_map_file *map_file)
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
	check_colision_move(player, map_file, dir);
}

void	player_rotate(t_player *player, bool turn_right, bool turn_left)
{
	if (turn_right)
		rotate_vector_dbl(&player->dir, ROT_SPEED);
	if (turn_left)
		rotate_vector_dbl(&player->dir, -ROT_SPEED);
	normalize_vector_dbl(&player->dir);
}

void	update_v_plane(t_player *player)
{
	t_vector_dbl	plane;

	plane.x = player->dir.x;
	plane.y = player->dir.y;
	rotate_vector_dbl(&plane, 90);
	player->v_plane.x = plane.x * (player->fov / 100);
	player->v_plane.y = plane.y * (player->fov / 100);
}
