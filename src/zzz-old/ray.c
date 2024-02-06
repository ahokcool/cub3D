/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:28:29 by astein            #+#    #+#             */
/*   Updated: 2024/02/06 21:18:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return (red << 16 | green << 8 | blue);
}

void put_pixel_to_image(t_cub *cub, void *mlx_ptr, void *img_ptr, int x, int y, int color)
{
    char    *image_data;
    int     bits_per_pixel;
    int     size_line;
    int     endian;

	if(x<0 || x>= cub->win.win_width || y<0 || y>= cub->win.win_height)
		return;
    // Get the image data address
    image_data = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

    // Calculate the position in the memory block (considering it as an array) where the pixel color should be set
    // Note: Assuming the window uses 32 bits per pixel
    int pixel_position = (y * size_line) + (x * (bits_per_pixel / 8));

    // Assuming little endian and ARGB format, set the pixel color
    // Note: You might need to adjust this based on the actual image format
    *(unsigned int *)(image_data + pixel_position) = color;
}

void	draw_sky_floor(t_cub *cub)
{
	int i;
	int y;
	int screen_middle_y;
	int color_floor;
	int color_sky;

	color_floor = 0x00B050;
	color_sky = 0x87CEEB;
	
	i = 0;
	screen_middle_y = cub->win.win_height / 2;
	while (i < cub->win.win_width)
	{
		y = 0;
		while(y < screen_middle_y)
			put_pixel_to_image(cub, cub->win.mlx, cub->img_ray.mlx_img, i, y++, color_sky);
		while(y < cub->win.win_height)
			put_pixel_to_image(cub, cub->win.mlx, cub->img_ray.mlx_img, i, y++, color_floor);
		
		i++;
	}
}

void	update_ray_frame(t_cub *cub)
{
	char    *pixel;
    int		i;
	int		x;
	int		y;

	x = 150;
	y = 150;
	int	color;
	
	draw_sky_floor(cub);
	color = encode_rgb(255,0,0);
    i = cub->img_ray.bpp - 8;
    pixel = cub->img_ray.addr + (y * cub->img_ray.line_len + x * (cub->img_ray.bpp / 8));
    while (i >= 0)
    {
        /* big endian, MSB is the leftmost bit */
        if (cub->img_ray.endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        /* little endian, LSB is the leftmost bit */
        else
            *pixel++ = (color >> (cub->img_ray.bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
	draw_rays(cub);
}

void	fill_empty_columns(t_cub *cub)
{
	// create average values for black spots columns because no ray was generated
	int i;

	i = 0;
	while (i < cub->win.win_width)
	{
		if (cub->colums[i].height == -1)
		{
			if(i == 0)
				cub->colums[i].height = cub->colums[i + 1].height;
			else if(i == cub->win.win_width - 1)
				cub->colums[i].height = cub->colums[i - 1].height;
			else
				cub->colums[i].height = (cub->colums[i - 1].height + cub->colums[i + 1].height) / 2;
		}
		// printf("(x %d h: %d)\n", i, cub->colums[i].height);	
		i++;
	}
}



void	calculate_rays(t_cub *cub)
{
	int i;
	double delta_rot;
	double current_rot;
	double	deltaDistX;
	double	deltaDistY;
	int screen_x;
	int sign_x;
	int sign_y;
	bool hit_x;
	bool hit_y;
	int cur_map_x;
	int cur_map_y;
	double euclidean_distance;
	double perpenducular_distance;
	double test_angle;
	double grid_offset_x;
	double grid_offset_y;
	t_vector_dbl vector_ray;

	i = 0;
	while (i < cub->win.win_width)
	{
		cub->colums[i].height = -1;
		cub->colums[i].x_hit_pos = -1;
		cub->colums[i].y_hit_pos = -1;
		i++;
	}
	
	current_rot = cub->player.rot_angle;
	 add_angle(&current_rot, (double)-(FOV / 2));
	// test_angle = 30;
	// add_angle(&current_rot, -test_angle);
	delta_rot = (double)FOV / cub->win.win_width;
	// delta_rot = 30;

	screen_x = 0;
	while (screen_x < cub->win.win_width)
	{
		angleToVector(current_rot, &vector_ray);
		if (vector_ray.x == 0)
			deltaDistX = 9999999999;
		else
			deltaDistX = sqrt(1 + (vector_ray.y * vector_ray.y) / (vector_ray.x * vector_ray.x));
		if (vector_ray.y == 0)
			deltaDistY = 9999999999;
		else
      		deltaDistY = sqrt(1 + (vector_ray.x * vector_ray.x) / (vector_ray.y * vector_ray.y));
		
		
		// player position in grid
		cur_map_x = (int)cub->player.pos_x;
		cur_map_y = (int)cub->player.pos_y;

		// define walking direction and initial distance to a grid
		grid_offset_x = 0;
		grid_offset_y = 0;
		if (vector_ray.x < 0)
		{
			sign_x = -1;
			grid_offset_x = (cub->player.pos_x - cur_map_x) * deltaDistX;
		}
		else
		{
			sign_x = 1;
			grid_offset_x = (cur_map_x + 1.0 - cub->player.pos_x) * deltaDistX;
		}
		if (vector_ray.y < 0)
		{
			sign_y = -1;
			grid_offset_y = (cub->player.pos_y - cur_map_y) * deltaDistY;
		}
		else
		{
			sign_y = 1;
			grid_offset_y = (cur_map_y + 1.0 - cub->player.pos_y) * deltaDistY;
		}
		// printf("RAY: rot %f, x: %f y: %f \n", current_rot, vector_ray.x, vector_ray.y);
		// printf("deltaDistX: %f, deltaDistY: %f \n", deltaDistX, deltaDistY);
		


		// DDA
		hit_x = false;
		hit_y = false;
		
		// printf("start dda for screen_x: %d\n", screen_x);
		while (!hit_x && !hit_y)
		{
			// printf("DDA: cur_map_x: %d, cur_map_y: %d\n", cur_map_x, cur_map_y);
			//jump to next map square, either in x-direction, or in y-direction

			if (grid_offset_x < grid_offset_y)
			{
				cur_map_x += sign_x;
				grid_offset_x += deltaDistX;
				cub->colums[screen_x].x_hit = true;
			}
			else
			{
				cur_map_y += sign_y;
				grid_offset_y += deltaDistY;
				cub->colums[screen_x].x_hit = false;
			}
			put_pixel_to_image(cub, cub->win.mlx, cub->img_2d.mlx_img, (cur_map_x*MAP2D_PIXEL_WIDTH)+MAP2D_PIXEL_WIDTH/2, (cur_map_y*MAP2D_PIXEL_WIDTH)+MAP2D_PIXEL_WIDTH/2, 0xFF0FF0);
			
			
			if(cub->map[cur_map_y][cur_map_x] == '1')
			{
				

				euclidean_distance = sqrt((cur_map_x - cub->player.pos_x) * (cur_map_x - cub->player.pos_x) + (cur_map_y - cub->player.pos_y) * (cur_map_y - cub->player.pos_y));
				// cub->colums[screen_x].x_hit = true;
				cub->colums[screen_x].x_hit_pos = cur_map_x;
				cub->colums[screen_x].y_hit_pos = cur_map_y;
				// perpenducular_distance = euclidean_distance * cos((current_rot)* (M_PI / 180));
				// perpenducular_distance = euclidean_distance * cos((current_rot)* (M_PI / 180));
				// perpenducular_distance = euclidean_distance * cos((current_rot - cub->player.rot_angle)* (M_PI / 180));
				
				// this wokrks!
				if(cub->colums[screen_x].x_hit)
					perpenducular_distance = grid_offset_x - deltaDistX;
				else
					perpenducular_distance = grid_offset_y - deltaDistY;
				
				double wallX; //where exactly the wall was hit
      			if(cub->colums[screen_x].x_hit = true)
				{
					wallX = cub->player.pos_y + perpenducular_distance * vector_ray.y;
					cub->colums[screen_x].x_hit_pos = wallX;
				}
	  			else
				{
					wallX = cub->player.pos_x + perpenducular_distance * vector_ray.x;
					cub->colums[screen_x].x_hit_pos = wallX;
				}
				wallX -= floor((wallX));
				// Assuming 'current_rot' is the ray's current angle and 'player.rot_angle' is the player's viewing angle.
				// double ray_angle_diff = fabs(current_rot - cub->player.rot_angle); // Ensure positive value
				// ray_angle_diff = ray_angle_diff * (M_PI / 180.0); // Convert to radians
				// perpenducular_distance = euclidean_distance * cos(ray_angle_diff); // Correct distance
				
				
				
				// perpenducular_distance = euclidean_distance * cos((current_rot - cub->player.rot_angle)* (M_PI / 180));
				// double angle_diff = current_rot - cub->player.rot_angle;
				// perpenducular_distance = euclidean_distance * cos(angle_diff * (M_PI / 180));
				
				cub->colums[screen_x].height = ((1/ perpenducular_distance) * (double)WALL_HEIGHT);
				// printf("hit at (%d,%d) ", cur_map_x, cur_map_y);
				put_pixel_to_image(cub, cub->win.mlx, cub->img_2d.mlx_img, cur_map_x*MAP2D_PIXEL_WIDTH, cur_map_y*MAP2D_PIXEL_WIDTH, 0xFF0000);
				hit_x = true;
			}
		}

		// printf("cur_rot %f, delta_rot: %f\n", current_rot, delta_rot);
		add_angle(&current_rot, delta_rot);
		screen_x++;
		// screen_x += cub->win.win_width / 3;
		// break;
	}
	// fill_empty_columns(cub);
}



void	draw_rays(t_cub *cub)
{
	int i;
	int y;
	int y_start;
	int screen_middle_y;

	i = 0;
	screen_middle_y = cub->win.win_height / 2;
	while (i < cub->win.win_width)
	{
		y_start = screen_middle_y - (cub->colums[i].height / 2);
		while (y_start < screen_middle_y + (cub->colums[i].height / 2))
		{
			put_pixel_to_image(cub, cub->win.mlx, cub->img_ray.mlx_img, i, y_start, 0xFF00FF);
			// double opacity = y_start / 600;
			// opacity = 0.4;
			// printf("opacity %f", opacity);
			// put_pixel_to_image_with_opacity(cub, cub->win.mlx, cub->img_ray.mlx_img, i, y_start, 0xFFFF0000, opacity);
			// blend_pixel_to_image(cub, cub->img_ray.mlx_img, i, y_start, 0xFF0000, cub->colums[i].height/300);
			y_start++;
		}
		i++;
	}
}

// uint8_t blend_colors(unsigned int existing_color, unsigned int new_color, double opacity)
// {
//     // Extract color components
//     unsigned int existing_alpha = (existing_color >> 24) & 0xFF;
//     unsigned int existing_red = (existing_color >> 16) & 0xFF;
//     unsigned int existing_green = (existing_color >> 8) & 0xFF;
//     unsigned int existing_blue = existing_color & 0xFF;

//     unsigned int new_red = (new_color >> 16) & 0xFF;
//     unsigned int new_green = (new_color >> 8) & 0xFF;
//     unsigned int new_blue = new_color & 0xFF;

//     // Blend each component
//     unsigned int red = (unsigned int)(existing_red * (1 - opacity) + new_red * opacity);
//     unsigned int green = (unsigned int)(existing_green * (1 - opacity) + new_green * opacity);
//     unsigned int blue = (unsigned int)(existing_blue * (1 - opacity) + new_blue * opacity);

//     // Assuming the result is fully opaque (alpha = 255), but you could adjust this
//     unsigned int alpha = 0xFF;

//     // Combine blended components back into a single color
// 	return(encode_rgb(red, green, blue));
//     // return (alpha << 24) | (red << 16) | (green << 8) | blue;
// }

// void put_pixel_to_image_with_opacity(t_cub *cub, void *mlx_ptr, void *img_ptr, int x, int y, int new_color, float opacity)
// {
//     char    *image_data;
//     int     bits_per_pixel;
//     int     size_line;
//     int     endian;

//     if(x<0 || x>= cub->win.win_width || y<0 || y>= cub->win.win_height)
//         return;

//     // Get the image data address
//     image_data = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

//     // Calculate the position in the memory block (considering it as an array) where the pixel color should be set
//     // Note: Assuming the window uses 32 bits per pixel
//     int pixel_position = (y * size_line) + (x * (bits_per_pixel / 8));

//     // Retrieve existing pixel color
//     unsigned int existing_color = *(unsigned int *)(image_data + pixel_position);
    
//     // Blend the new color with the existing color based on the opacity
//     // unsigned int blended_color = 

//     // Set the blended pixel color
//     *(unsigned int *)(image_data + pixel_position) = blend_colors(existing_color, new_color, opacity);;
// }




// void blend_pixel_to_image(t_cub *cub, void *mlx_img, int x, int y, int new_color, float opacity) {
//     int existing_color;
//     int blended_color;
//     int red, green, blue;

//     // Assuming get_pixel_color is a function you have that retrieves the color of a pixel at (x, y)
//     existing_color = new_color;

//     // Extract individual color components from each color
//     int existing_red = (existing_color >> 16) & 0xFF;
//     int existing_green = (existing_color >> 8) & 0xFF;
//     int existing_blue = existing_color & 0xFF;

//     int new_red = (new_color >> 16) & 0xFF;
//     int new_green = (new_color >> 8) & 0xFF;
//     int new_blue = new_color & 0xFF;

//     // Blend each component separately
//     red = (int)((new_red * opacity) + (existing_red * (1.0 - opacity)));
//     green = (int)((new_green * opacity) + (existing_green * (1.0 - opacity)));
//     blue = (int)((new_blue * opacity) + (existing_blue * (1.0 - opacity)));

//     // Combine blended components back into a single color
//     blended_color = (red << 16) | (green << 8) | blue;

//     // Assuming put_pixel_to_image is a function you have that sets the color of a pixel at (x, y)
//     put_pixel_to_image(cub, cub->win.mlx, mlx_img, x, y, blended_color);
// }
