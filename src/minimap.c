/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:19:58 by astein            #+#    #+#             */
/*   Updated: 2024/02/02 17:34:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_tile(t_cub *cub, int x, int y, t_img *img)
{
	int	i;
	int	j;
	char *src_pxl;
	char *dst_pxl;
	
	i = 0;
	while (i < MINIMAP_PIXEL_WIDTH)
	{
		j = 0;
		while (j < MINIMAP_PIXEL_WIDTH)
		{
			// dprintf (2, "(%d,%d)", i, j);
			src_pxl = img->addr + (i * img->line_len + j * (img->bpp / 8));
			if ((y + i) < cub->img_mini.height && (x + j) < cub->img_mini.width)
			{
				dst_pxl = cub->img_mini.addr + ((y + i) * cub->img_mini.line_len + (x + j) * (cub->img_mini.bpp / 8));
				*(unsigned int*)dst_pxl = *(unsigned int*)src_pxl;
			}
			else
				printf("put_tile (%d, %d) out of bounds\n", x + j, y + i);
			j++;
		}
		i++;
	}	
}

void	ini_minimap(t_cub *cub)
{
	int dim_x;
	int dim_y;

	// Check if minimap size is valid, if not correct it
	cub->minimap.map_border = 2*MINIMAP_BORDER_SIZE+1;
	ft_matrix_dim(cub->map, &dim_x, &dim_y);
	if (cub->minimap.map_border > dim_x)
		cub->minimap.map_border = dim_x;
	if (cub->minimap.map_border > dim_y)
		cub->minimap.map_border = dim_y;
	cub->minimap.map_border = (cub->minimap.map_border -1) / 2;
	printf ("mini map size: %d\n", cub->minimap.map_border);
	cub->minimap.mini_map_str = ft_calloc(((2*MINIMAP_BORDER_SIZE+1)*(2*MINIMAP_BORDER_SIZE+1)+1), sizeof(char));
	cub->minimap.wall.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/wall.xpm", &cub->minimap.wall.width, &cub->minimap.wall.height);
	cub->minimap.empty.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/floor.xpm", &cub->minimap.empty.width, &cub->minimap.empty.height);
	cub->minimap.player_N.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_N.xpm", &cub->minimap.player_N.width, &cub->minimap.player_N.height);
	cub->minimap.player_E.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_E.xpm", &cub->minimap.player_E.width, &cub->minimap.player_E.height);
	cub->minimap.player_S.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_S.xpm", &cub->minimap.player_S.width, &cub->minimap.player_S.height);
	cub->minimap.player_W.mlx_img = mlx_xpm_file_to_image(cub->win.mlx, "./textures/minimap/player_W.xpm", &cub->minimap.player_W.width, &cub->minimap.player_W.height);
	cub->minimap.wall.addr = mlx_get_data_addr(cub->minimap.wall.mlx_img, &cub->minimap.wall.bpp, &cub->minimap.wall.line_len, &cub->minimap.wall.endian);
	cub->minimap.empty.addr = mlx_get_data_addr(cub->minimap.empty.mlx_img, &cub->minimap.empty.bpp, &cub->minimap.empty.line_len, &cub->minimap.empty.endian);
	cub->minimap.player_N.addr = mlx_get_data_addr(cub->minimap.player_N.mlx_img, &cub->minimap.player_N.bpp, &cub->minimap.player_N.line_len, &cub->minimap.player_N.endian);
	cub->minimap.player_E.addr = mlx_get_data_addr(cub->minimap.player_E.mlx_img, &cub->minimap.player_E.bpp, &cub->minimap.player_E.line_len, &cub->minimap.player_E.endian);
	cub->minimap.player_S.addr = mlx_get_data_addr(cub->minimap.player_S.mlx_img, &cub->minimap.player_S.bpp, &cub->minimap.player_S.line_len, &cub->minimap.player_S.endian);
	cub->minimap.player_W.addr = mlx_get_data_addr(cub->minimap.player_W.mlx_img, &cub->minimap.player_W.bpp, &cub->minimap.player_W.line_len, &cub->minimap.player_W.endian);
}

static	void set_minimap_area(t_cub *cub)
{
	cub->minimap.x0 = get_player_pos(cub, 'x') - cub->minimap.map_border;
	cub->minimap.y0 = get_player_pos(cub, 'y') - cub->minimap.map_border;
	cub->minimap.x1 = get_player_pos(cub, 'x') + cub->minimap.map_border;
	cub->minimap.y1 = get_player_pos(cub, 'y') + cub->minimap.map_border;

	if (cub->minimap.x0 < 0)
	{
		cub->minimap.x0 = 0;
		cub->minimap.x1 = cub->minimap.map_border * 2 +1;
		printf("x0 < 0\n");
	}
	if (cub->minimap.y0 < 0)
	{
		cub->minimap.y0 = 0;
		cub->minimap.y1 = cub->minimap.map_border * 2 +1;
		printf("y0 < 0\n");
	}
	// if (cub->minimap.x1 > cub->map.
	// {
	// 	cub->minimap.x1 = dim_x;
	// 	cub->minimap.x0 = dim_x - mapsize;
	// }
	// if (cub->minimap.y1 > dim_y)
	// {
	// 	cub->minimap.y1 = dim_y;
	// 	cub->minimap.y0 = dim_y - mapsize;
	// }
}
static void	update_minimap_string(t_cub *cub)
{
	int	i;
	int player[2];
	int cord[2];

	i = 0;
	player[0] = get_player_pos(cub, 'x');
	player[1] = get_player_pos(cub, 'y');
	cord[0] = cub->minimap.x0;
	cord[1] = cub->minimap.y0;
	printf("update minimap string x:%d->%d, y:%d->%d\n", cub->minimap.x0, cub->minimap.x1, cub->minimap.y0, cub->minimap.y1);
	while (cord[1] <= cub->minimap.y1)
	{
		while (cord[0] <= cub->minimap.x1)
		{
			if (cord[0] == (int)player[0] && cord[1] == (int)player[1])
				cub->minimap.mini_map_str[i] = 'P';
			else
				cub->minimap.mini_map_str[i] = cub->map[cord[1]][cord[0]];
			i++;
			cord[0]++;
		}
		cord[1]++;
		cord[0] = cub->minimap.x0;
	}
	printf("string i: %d\n", i);
	printf("string length = %d\n", (int)ft_strlen(cub->minimap.mini_map_str));
	printf("minimap string: (%s)\n", cub->minimap.mini_map_str);
}

void	minimap_main(t_cub *cub)
{
	set_minimap_area(cub);
	update_minimap_string(cub);
}

void	update_minimap_frame(t_cub *cub)
{
	// put_wall(cub, 0, 0);
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (cub->minimap.mini_map_str[i])
	{
	
		if(cub->minimap.mini_map_str[i] == '1')
			put_tile(cub, x, y, &cub->minimap.wall);
		else if(cub->minimap.mini_map_str[i] == 'P')
		{
			if (cub->player.rot_angle == 0)
				put_tile(cub, x, y, &cub->minimap.player_N);
			else if (cub->player.rot_angle == 90)
				put_tile(cub, x, y, &cub->minimap.player_E);
			else if (cub->player.rot_angle == 180)
				put_tile(cub, x, y, &cub->minimap.player_S);
			else if (cub->player.rot_angle == 270)
				put_tile(cub, x, y, &cub->minimap.player_W);
		}
		else
			put_tile(cub, x, y, &cub->minimap.empty);
		x += MINIMAP_PIXEL_WIDTH;
		if(x >= cub->img_mini.width)
		{
			y += MINIMAP_PIXEL_WIDTH;
			x = 0;
		}
		i++;
	}	
	ft_putchar_fd('\n', STDOUT_FILENO);
	printf("----\n");
}