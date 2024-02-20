/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:52:12 by astein            #+#    #+#             */
/*   Updated: 2024/02/20 20:54:06 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map3d(t_map3d *map3d)
{
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
		ini_column(&map3d->columns[i]);
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

void	update_map3d(t_map3d *map3d, t_player *player, t_map_file *map_file)
{
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
	{
		update_column(&map3d->columns[i], player, map_file, i);
	}
}

static void	draw_wall_clr(t_cub *cub, int x_screen, int y_end, int *y)
{
	int wall_color;

		if (cub->map3d.columns[x_screen].hit_direction == 'N')
			wall_color = (int)CLR_NORTH;
		else if (cub->map3d.columns[x_screen].hit_direction == 'S')
			wall_color = (int)CLR_SOUTH;
		else if (cub->map3d.columns[x_screen].hit_direction == 'E')
			wall_color = (int)CLR_EAST;
		else if (cub->map3d.columns[x_screen].hit_direction == 'W')
			wall_color = (int)CLR_WEST;
	while (++(*y) <= y_end) // Ensure y is within the screen bounds
		if (*y >= 0 && *y < WIN_HEIGHT)
			set_pixel_to_image(&cub->img_3d, x_screen, *y, wall_color);
}

static void	draw_wall_xpm(t_cub *cub, int x_screen, int y_end, int *y)
{
	t_img *texture;
	t_img *win;

	if (cub->map3d.columns[x_screen].hit_direction == 'N')
		texture = &cub->map3d.img_wall_no;
	else if (cub->map3d.columns[x_screen].hit_direction == 'S')
		texture = &cub->map3d.img_wall_so;
	else if (cub->map3d.columns[x_screen].hit_direction == 'E')
		texture = &cub->map3d.img_wall_ea;
	else
		texture = &cub->map3d.img_wall_we;
	win = &cub->img_3d;

	//        // How much ttexNumo increase the texture coordinate per screen pixel
    //   double step = 1.0 * texHeight / lineHeight;
    // //   double step = 1.0 * xpm->height / xpm->line_len; --- EXMAPLE!!!
    //   // Starting texture coordinate
    //   double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
    //   for(int y = drawStart; y<drawEnd; y++)
    //   {
    //     // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
    //     int texY = (int)texPos & (texHeight - 1);
    //     texPos += step;
    //     Uint32 color = texture[texNum][texHeight * texY + texX];
    //     //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
    //     if(side == 1) color = (color >> 1) & 8355711;
    //     buffer[y][x] = color;
    //   }  
	// 

	char 			*text_pxl;
	char 			*win_pxl;
	t_vector_dbl	text_pos;
	t_vector_dbl	win_pos;

	win_pos.x = x_screen;
	win_pos.y = *y;

	// the x position in the texture we want to compy the pixels from
	text_pos.x = (double)texture->width * cub->map3d.columns[x_screen].wall_x;
	printf("text_pos.x %f\n",text_pos.x);

	text_pos.y = 0;

	// x pos of texture
	// int tex_x = (int)(cub->map3d.columns[x_screen].wall_x * (double)texture->width);
    // tex_x = texture->width - tex_x - 1;
	// printf("texX %d\n",tex_x);
	
	double step = 1.0 * texture->height / cub->map3d.columns[x_screen].height;
	printf("step %f\n",step);
	
	// cur_text_pos_y is the current pos_y in texture as double
	double cur_text_pos_y = (*y - 600.0 / 2 + texture->line_len / 2) * step;
	// printf("text pos  %f\n",cur_text_pos_y);

	// if(x_screen == WIN_WIDTH)
		printf("wall heugt: %d\n",cub->map3d.columns[x_screen].height);
	// int	tex_y;
	// uint32_t color;
	
	// t_img *dest;
	// dest = &cub->img_3d;


	while (++(*y) <= y_end) // Ensure y is within the screen bounds
	{
		win_pos.y = *y;
		text_pos.y += step;

		// 1 find the pixel in the texure we want to copy from
		text_pxl = texture->addr + ((int)text_pos.y * texture->line_len + (int)text_pos.x * (texture->bpp / 8));

		// 2. find the pixel in the window where we want to copy to
		win_pxl = win->addr + ((int)win_pos.y * win->line_len + (int)win_pos.x * (win->bpp / 8));

		// 3. copy the fucking pixel
		*(unsigned int*)win_pxl = *(unsigned int*)text_pxl;



	// 	tex_y = (int)cur_text_pos_y & (texture->height - 1);
	// 	cur_text_pos_y += step;
	// 	color = texture->addr[texture->height * tex_y + tex_x];
	// 	text_pxl = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
	// 	win_pxl = dest->addr + ((*y) * dest->line_len + (x_screen) * (dest->bpp / 8));
	// 	*(unsigned int*)win_pxl = *(unsigned int*)text_pxl;
	// 	// set_pixel_to_image(&cub->img_3d, x_screen, *y, color);
	}
}

static void	draw_wall(t_cub *cub, int x_screen, int y_end, int *y)
{
	(*y)--;
	if (cub->controller.show_texture)
		draw_wall_xpm(cub, x_screen, y_end, y);
	else
		draw_wall_clr(cub, x_screen, y_end, y);
}

void	update_map3d_frame(t_cub *cub)
{
	int x_screen;
	int y;
	// int height;
	int y_start;
	int y_end;
	int screen_middle_y;

	x_screen = 0;
	screen_middle_y = WIN_HEIGHT / 2 - 1;
	while (x_screen < WIN_WIDTH)
	{
		y_start = fmax(0, screen_middle_y - (cub->map3d.columns[x_screen].height / 2));
		y_end = fmin(WIN_HEIGHT - 1, screen_middle_y + (cub->map3d.columns[x_screen].height / 2));
		y = -1;
		// Draw sky
		while (++y < y_start)
    		if (y >= 0 && y < WIN_HEIGHT)
        		set_pixel_to_image(&cub->img_3d, x_screen, y, cub->map_file.rgb_ceiling);
		
		// Draw wall
		draw_wall(cub, x_screen, y_end, &y);
		
		// Draw floor
		y--;
		while (++y < WIN_HEIGHT)
    		set_pixel_to_image(&cub->img_3d, x_screen, y, cub->map_file.rgb_floor);
		x_screen++;
	}
}

void	destroy_map3d(void *mlx, t_map3d *map3d)
{
	destroy_img(mlx, &map3d->img_wall_no);
	destroy_img(mlx, &map3d->img_wall_we);
	destroy_img(mlx, &map3d->img_wall_so);
	destroy_img(mlx, &map3d->img_wall_ea);
}