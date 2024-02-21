/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:05:38 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 19:17:29 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_clr(t_cub *cub, int win_pos_x)
{
	int	cur_y;
	int	wall_color;

	cur_y = cub->map3d.columns[win_pos_x].wall_start_y;
	if (cub->map3d.columns[win_pos_x].hit_direction == 'N')
		wall_color = (int)CLR_NORTH;
	else if (cub->map3d.columns[win_pos_x].hit_direction == 'S')
		wall_color = (int)CLR_SOUTH;
	else if (cub->map3d.columns[win_pos_x].hit_direction == 'E')
		wall_color = (int)CLR_EAST;
	else if (cub->map3d.columns[win_pos_x].hit_direction == 'W')
		wall_color = (int)CLR_WEST;
	while (cur_y < cub->map3d.columns[win_pos_x].wall_end_y)
	{
		if (cur_y >= 0 && cur_y < WIN_HEIGHT)
			set_pixel_to_image(&cub->img_3d, win_pos_x, cur_y, wall_color);
		cur_y++;
	}
}
static void	choose_texture(t_cub *cub, int win_pos_x, t_img **src, t_img **dest)
{
	if (cub->map3d.columns[win_pos_x].hit_direction == 'N')
		*src = &cub->map3d.img_wall_no;
	else if (cub->map3d.columns[win_pos_x].hit_direction == 'S')
		*src = &cub->map3d.img_wall_so;
	else if (cub->map3d.columns[win_pos_x].hit_direction == 'E')
		*src = &cub->map3d.img_wall_ea;
	else
		*src = &cub->map3d.img_wall_we;
	*dest = &cub->img_3d;
}

static void	draw_wall_xpm(t_cub *cub, int win_pos_x)
{
	t_img			*texture;
	t_img			*win;
	char			*text_pxl;
	char			*win_pxl;
	t_vector_dbl	text_pos;
	t_vector_int	win_pos;
	double			step;
	int				cur_y;
	double			cur_text_pos_y;

	cur_y = cub->map3d.columns[win_pos_x].wall_start_y;
	choose_texture(cub, win_pos_x, &texture, &win);
	win_pos.x = win_pos_x;
	win_pos.y = cur_y;
	if (cub->map3d.columns[win_pos_x].hit_direction == 'S'
		|| cub->map3d.columns[win_pos_x].hit_direction == 'W')
		text_pos.x = (double)texture->width
			* cub->map3d.columns[win_pos_x].wall_x;
	else
		text_pos.x = ((double)texture->width * (1.0
					- cub->map3d.columns[win_pos_x].wall_x));
	step = 1.0 * texture->height / cub->map3d.columns[win_pos_x].height;
	if (cub->map3d.columns[win_pos_x].height < cub->win.win_height)
		text_pos.y = 0.0;
	else
	{
		text_pos.y = (((((double)cub->map3d.columns[win_pos_x].height
							- (double)cub->win.win_height) / 2)
					/ (double)cub->map3d.columns[win_pos_x].height)
				* (double)texture->height);
		step = 1 - ((double)(cub->map3d.columns[win_pos_x].height
					- (double)cub->win.win_height)
				/ (double)cub->map3d.columns[win_pos_x].height);
		step *= (double)texture->height;
		step /= (double)cub->win.win_height;
	}
	cur_text_pos_y = (cur_y - 600.0 / 2 + texture->line_len / 2) * step;
	while (cur_y < cub->map3d.columns[win_pos_x].wall_end_y)
	{
		win_pos.y = cur_y;
		text_pxl = texture->addr + ((int)(text_pos.y) * texture->line_len
				+ (int)(text_pos.x) * (texture->bpp / 8));
		win_pxl = win->addr + ((int)(win_pos.y) * win->line_len
				+ (int)(win_pos.x) * (win->bpp / 8));
		*(unsigned int *)win_pxl = *(unsigned int *)text_pxl;
		text_pos.y += step;
		cur_y++;
	}
}

void	draw_wall(t_cub *cub, int x_screen)
{
	if (cub->controller.show_texture)
		draw_wall_xpm(cub, x_screen);
	else
		draw_wall_clr(cub, x_screen);
}
