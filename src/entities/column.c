/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:17:03 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 20:27:31 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_col(t_pxl_col *col)
{
	col->perp_dist = 0;
	col->height = 0;
	col->hit_direction = 0;
	col->hit_pos.x = -1;
	col->hit_pos.y = -1;
	col->ray.x = 0;
	col->ray.y = 0;
	col->wall_start_y = -1;
	col->wall_end_y = -1;
}

static void	config_dda(t_pxl_col *col, t_player *player, t_dda *dda)
{
	dda->tile.x = (int)player->pos.x;
	dda->tile.y = (int)player->pos.y;
	dda->d_dist.x = fabs(1 / col->ray.x);
	dda->d_dist.y = fabs(1 / col->ray.y);
	if (col->ray.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (player->pos.x - dda->tile.x) * dda->d_dist.x;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = (dda->tile.x + 1.0 - player->pos.x) * dda->d_dist.x;
	}
	if (col->ray.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (player->pos.y - dda->tile.y) * dda->d_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->tile.y + 1.0 - player->pos.y) * dda->d_dist.y;
	}
	dda->hit = 0;
}

static void	calculate_hit(t_pxl_col *col, t_player *player, t_dda *dda)
{
	if (dda->side == 0)
	{
		col->perp_dist = (dda->tile.x - player->pos.x + (1 - dda->step.x) / 2)
			/ col->ray.x;
		if (col->ray.x > 0)
			col->hit_direction = 'W';
		else
			col->hit_direction = 'E';
	}
	else
	{
		col->perp_dist = (dda->tile.y - player->pos.y + (1 - dda->step.y) / 2)
			/ col->ray.y;
		if (col->ray.y > 0)
			col->hit_direction = 'N';
		else
			col->hit_direction = 'S';
	}
}

static void	calculate_wall(t_pxl_col *col, t_player *player)
{
	int	screen_middle_y;

	col->height = (int)((1 / col->perp_dist) * (double)WALL_HEIGHT);
	col->hit_pos.x = player->pos.x + col->perp_dist * col->ray.x;
	col->hit_pos.y = player->pos.y + col->perp_dist * col->ray.y;
	if (col->hit_direction == 'N' || col->hit_direction == 'S')
	{
		col->wall_x = col->hit_pos.x;
		col->wall_x -= floor(col->wall_x);
	}
	else
	{
		col->wall_x = col->hit_pos.y;
		col->wall_x -= floor(col->wall_x);
	}
	screen_middle_y = WIN_HEIGHT / 2 - 1;
	col->wall_start_y = fmax(0, screen_middle_y - (col->height / 2));
	col->wall_end_y = fmin(WIN_HEIGHT - 1, screen_middle_y
			+ ((int)ceil(col->height / 2)));
}

void	config_col(t_pxl_col *col, t_player *player, t_map_file *map_file,
	int col_i)
{
	t_dda			dda;

	dda.camera_x = ((2 * col_i / (double)WIN_WIDTH) - 1);
	col->ray.x = (player->dir.x + player->v_plane.x * dda.camera_x) * 20;
	col->ray.y = (player->dir.y + player->v_plane.y * dda.camera_x) * 20;
	config_dda(col, player, &dda);
	while (!dda.hit)
	{
		if (dda.side_dist.x < dda.side_dist.y)
		{
			dda.side_dist.x += dda.d_dist.x;
			dda.tile.x += dda.step.x;
			dda.side = 0;
		}
		else
		{
			dda.side_dist.y += dda.d_dist.y;
			dda.tile.y += dda.step.y;
			dda.side = 1;
		}
		if (map_file->map[dda.tile.y][dda.tile.x] == '1')
			dda.hit = 1;
	}
	calculate_hit(col, player, &dda);
	calculate_wall(col, player);
}
