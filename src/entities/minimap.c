/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:19:58 by astein            #+#    #+#             */
/*   Updated: 2024/02/20 16:21:19 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_minimap(t_minimap *minimap)
{
	ini_img(&minimap->img_wall);
	ini_img(&minimap->img_floor);
	minimap->map_mini = NULL;
	minimap->size = -1;
}

void	config_minimap(t_cub *cub, t_minimap *minimap, char **map)
{
	t_vector_int	dim;

	// Check if minimap size is valid, if not correct it
	minimap->size = 2*MINIMAP_BORDER_SIZE+1;
	ft_matrix_dim(map, &dim.x, &dim.y);
	if (minimap->size > dim.x)
		minimap->size = dim.x;
	if (minimap->size > dim.y)
		minimap->size = dim.y;
	config_img_file(cub, &minimap->img_wall, "./textures/minimap/wall.xpm");
	config_img_file(cub, &minimap->img_floor, "./textures/minimap/floor.xpm");
}	

void	destroy_minimap(void *mlx_ptr, t_minimap *minimap)
{
	destroy_img(mlx_ptr, minimap->img_wall.mlx_img);
	destroy_img(mlx_ptr, minimap->img_floor.mlx_img);
	free_whatever("m", minimap->map_mini);
}

void	update_mapmini_frame(t_cub *cub)
{
	(void)cub;
}





//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------





// static	void set_minimap_area(t_cub *cub)
// {
// 	cub->minimap.x0 = get_player_pos(cub, 'x') - cub->minimap.map_border;
// 	cub->minimap.y0 = get_player_pos(cub, 'y') - cub->minimap.map_border;
// 	cub->minimap.x1 = get_player_pos(cub, 'x') + cub->minimap.map_border;
// 	cub->minimap.y1 = get_player_pos(cub, 'y') + cub->minimap.map_border;

// 	if (cub->minimap.x0 < 0)
// 	{
// 		cub->minimap.x0 = 0;
// 		cub->minimap.x1 = cub->minimap.map_border * 2 +1;
// 		printf("x0 < 0\n");
// 	}
// 	if (cub->minimap.y0 < 0)
// 	{
// 		cub->minimap.y0 = 0;
// 		cub->minimap.y1 = cub->minimap.map_border * 2 +1;
// 		printf("y0 < 0\n");
// 	}
// 	// if (cub->minimap.x1 > cub->map.
// 	// {
// 	// 	cub->minimap.x1 = dim_x;
// 	// 	cub->minimap.x0 = dim_x - mapsize;
// 	// }
// 	// if (cub->minimap.y1 > dim_y)
// 	// {
// 	// 	cub->minimap.y1 = dim_y;
// 	// 	cub->minimap.y0 = dim_y - mapsize;
// 	// }
// }
// static void	update_minimap_string(t_cub *cub)
// {
// 	int	i;
// 	int player[2];
// 	int cord[2];

// 	i = 0;
// 	player[0] = get_player_pos(cub, 'x');
// 	player[1] = get_player_pos(cub, 'y');
// 	cord[0] = cub->minimap.x0;
// 	cord[1] = cub->minimap.y0;
// 	// printf("update minimap string x:%d->%d, y:%d->%d\n", cub->minimap.x0, cub->minimap.x1, cub->minimap.y0, cub->minimap.y1);
// 	while (cord[1] <= cub->minimap.y1)
// 	{
// 		while (cord[0] <= cub->minimap.x1)
// 		{
// 			if (cord[0] == (int)player[0] && cord[1] == (int)player[1])
// 				cub->minimap.mini_map_str[i] = 'P';
// 			else
// 				cub->minimap.mini_map_str[i] = cub->map[cord[1]][cord[0]];
// 			i++;
// 			cord[0]++;
// 		}
// 		cord[1]++;
// 		cord[0] = cub->minimap.x0;
// 	}
// 	// printf("string i: %d\n", i);
// 	// printf("string length = %d\n", (int)ft_strlen(cub->minimap.mini_map_str));
// 	printf("minimap string: (%s)\n", cub->minimap.mini_map_str);
// }

// void	minimap_main(t_cub *cub)
// {
// 	set_minimap_area(cub);
// 	update_minimap_string(cub);
// }

// // void	update_minimap_frame(t_cub *cub)
// // {
// // 	// put_wall(cub, 0, 0);
// // 	int	i;
// // 	int	x;
// // 	int	y;

// // 	i = 0;
// // 	x = 0;
// // 	y = 0;
// // 	while (cub->minimap.mini_map_str[i])
// // 	{
	
// // 		if(cub->minimap.mini_map_str[i] == '1')
// // 			put_tile(cub, x, y, &cub->minimap.img_wall, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 		else if(cub->minimap.mini_map_str[i] == 'P')
// // 		{
// // 			if (cub->player.rot_angle == 0)
// // 				put_tile(cub, x, y, &cub->minimap.player_N, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 			else if (cub->player.rot_angle == 45)
// // 				put_tile(cub, x, y, &cub->minimap.player_NE, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 			else if (cub->player.rot_angle == 90)
// // 				put_tile(cub, x, y, &cub->minimap.player_E, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 			else if (cub->player.rot_angle == 135)
// // 				put_tile(cub, x, y, &cub->minimap.player_SE, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 			else if (cub->player.rot_angle == 180)
// // 				put_tile(cub, x, y, &cub->minimap.player_S, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 			else if (cub->player.rot_angle == 225)
// // 				put_tile(cub, x, y, &cub->minimap.player_SW, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 			else if (cub->player.rot_angle == 270)
// // 				put_tile(cub, x, y, &cub->minimap.player_W, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 			else if (cub->player.rot_angle == 315)
// // 				put_tile(cub, x, y, &cub->minimap.player_NW, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 		}
// // 		else
// // 			put_tile(cub, x, y, &cub->minimap.img_floor, &cub->img_mini, MINIMAP_PIXEL_WIDTH);
// // 		x += MINIMAP_PIXEL_WIDTH;
// // 		if(x >= cub->img_mini.width)
// // 		{
// // 			y += MINIMAP_PIXEL_WIDTH;
// // 			x = 0;
// // 		}
// // 		i++;
// // 	}	
// // 	ft_putchar_fd('\n', STDOUT_FILENO);
// // 	printf("----\n");
// // }