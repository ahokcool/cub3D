/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:05:38 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 21:03:20 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_clr(t_cub *cub, int win_pos_x)
{
	int	cur_y;
	int	wall_color;

	cur_y = cub->map3d.cols[win_pos_x].wall_start_y;
	if (cub->map3d.cols[win_pos_x].hit_direction == 'N')
		wall_color = (int)CLR_NORTH;
	else if (cub->map3d.cols[win_pos_x].hit_direction == 'S')
		wall_color = (int)CLR_SOUTH;
	else if (cub->map3d.cols[win_pos_x].hit_direction == 'E')
		wall_color = (int)CLR_EAST;
	else if (cub->map3d.cols[win_pos_x].hit_direction == 'W')
		wall_color = (int)CLR_WEST;
	while (cur_y < cub->map3d.cols[win_pos_x].wall_end_y)
	{
		if (cur_y >= 0 && cur_y < WIN_HEIGHT)
			set_pixel_to_image(&cub->img_3d, win_pos_x, cur_y, wall_color);
		cur_y++;
	}
}

static void	config_draw_wall(t_cub *cub, t_draw_wall *w, int x_screen)
{
	w->win_pos.x = x_screen;
	w->win = &cub->img_3d;
	if (cub->map3d.cols[w->win_pos.x].hit_direction == 'N')
		w->text = &cub->map3d.img_wall_no;
	else if (cub->map3d.cols[w->win_pos.x].hit_direction == 'S')
		w->text = &cub->map3d.img_wall_so;
	else if (cub->map3d.cols[w->win_pos.x].hit_direction == 'E')
		w->text = &cub->map3d.img_wall_ea;
	else
		w->text = &cub->map3d.img_wall_we;
	w->cur_win_y = cub->map3d.cols[w->win_pos.x].wall_start_y;
	w->win_pos.x = w->win_pos.x;
	w->win_pos.y = w->cur_win_y;
	if (cub->map3d.cols[w->win_pos.x].hit_direction == 'S'
		|| cub->map3d.cols[w->win_pos.x].hit_direction == 'W')
		w->text_pos.x = (double)w->text->width
			* cub->map3d.cols[w->win_pos.x].wall_x;
	else
		w->text_pos.x = ((double)w->text->width * (1.0
					- cub->map3d.cols[w->win_pos.x].wall_x));
	w->step = 1.0 * w->text->height / cub->map3d.cols[w->win_pos.x].height;
}

static void	draw_wall_xpm(t_cub *cub, t_draw_wall *w)
{
	if (cub->map3d.cols[w->win_pos.x].height < cub->win.win_height)
		w->text_pos.y = 0.0;
	else
	{
		w->text_pos.y = (((((double)cub->map3d.cols[w->win_pos.x].height
							- (double)cub->win.win_height) / 2)
					/ (double)cub->map3d.cols[w->win_pos.x].height)
				* (double)w->text->height);
		w->step = ((1 - ((double)(cub->map3d.cols[w->win_pos.x].height - (double)cub->win.win_height) / (double)cub->map3d.cols[w->win_pos.x].height)) * (double)w->text->height) / (double)cub->win.win_height;
	}
	w->cur_text_y = (w->cur_win_y - 600.0 / 2 + w->text->line_l / 2) * w->step;
	while (w->cur_win_y < cub->map3d.cols[w->win_pos.x].wall_end_y)
	{
		w->win_pos.y = w->cur_win_y;
		w->text_pxl = w->text->addr + ((int)(w->text_pos.y) * w->text->line_l
				+ (int)(w->text_pos.x) * (w->text->bpp / 8));
		w->win_pxl = w->win->addr + ((int)(w->win_pos.y) * w->win->line_l
				+ (int)(w->win_pos.x) * (w->win->bpp / 8));
		*(unsigned int *)w->win_pxl = *(unsigned int *)w->text_pxl;
		w->text_pos.y += w->step;
		w->cur_win_y++;
	}
}

void	draw_wall(t_cub *cub, int x_screen)
{
	t_draw_wall		w;

	if (cub->controller.show_texture)
	{
		config_draw_wall(cub, &w, x_screen);
		draw_wall_xpm(cub, &w);
	}
	else
		draw_wall_clr(cub, x_screen);
}
