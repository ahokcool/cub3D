/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:37 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 09:25:41 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = -1;
	img->line_len = -1;
	img->endian = -1;
	img->width = -1;
	img->height = -1;
}

/**
 * @brief   This function can create a new image from a .xpm file path
 * 			If the file path is NULL, it will create an empty image with
 * 			the given dimensions. If the dimensions are NULL, it will
 * 			create an empty image with the default window dimensions.
 * 
 * @param   mlx         
 * @param   img         
 * @param   path        
 * @param   dimensions  
 */
void	config_img(void *mlx, t_img *img, char *path, t_vector_int *dimensions)
{
	if (path)
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &img->width,
				&img->height);
	else
	{
		if (dimensions)
		{
			img->mlx_img = mlx_new_image(mlx, dimensions->x, dimensions->y);
			if(img->mlx_img)
			{
				img->width = dimensions->x;
				img->height = dimensions->y;
			}
		}
		else
		{
			img->mlx_img = mlx_new_image(mlx, WIN_HEIGHT, WIN_HEIGHT);
			if(img->mlx_img)
			{
				img->width = WIN_WIDTH;
				img->height = WIN_HEIGHT;
			}
		}
	}
	if (img->mlx_img)
			img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
					&(img->line_len), &(img->endian));
		else
			printf("failed to load image from path");
}

void	destroy_img(void *mlx, t_img *img)
{
	if (img->mlx_img)
		mlx_destroy_image(mlx, img->mlx_img);
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = -1;
	img->line_len = -1;
	img->endian = -1;
	img->width = -1;
	img->height = -1;
}

//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


void	ini_img_2d(t_cub *cub, t_img *img)
{
	size_t	img_size;

	img->height = cub->win.win_height;
	img->width = cub->win.win_width;
	img->mlx_img = mlx_new_image(cub->win.mlx, cub->win.win_width, cub->win.win_height);
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
			&(img->line_len), &(img->endian));
	img_size = img->height * img->width * sizeof(img->bpp);
	ft_bzero(img->addr, img_size);
	printf("2d map image dimensions (%d, %d)\n", img->width, img->height);
}

void	ini_img_screen(t_cub *cub, t_img *img)
{
	size_t	img_size;

	img->height = cub->win.win_height;
	img->width = cub->win.win_width;
	img->mlx_img = mlx_new_image(cub->win.mlx, cub->win.win_width, cub->win.win_height);
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
			&(img->line_len), &(img->endian));
	img_size = img->height * img->width * sizeof(img->bpp);
	ft_bzero(img->addr, img_size);
	printf("ray image dimensions (%d, %d)\n", img->width, img->height);
}
void	ini_img_mini(t_cub *cub, t_img *img)
{
	size_t	img_size;
	int		heigth;

	heigth = MINIMAP_PIXEL_WIDTH*(MINIMAP_BORDER_SIZE*2+1);
	img->mlx_img = mlx_new_image(cub->win.mlx, heigth, heigth);
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
			&(img->line_len), &(img->endian));
	img_size = img->width * img->height * (img->bpp / 8);
	img->height = heigth;
	img->width = heigth;
	ft_bzero(img->addr, img_size);
	printf("minimap image dimensions (%d, %d)\n", img->width, img->height);
}


// void	img_pix_put(t_model *mod, t_pnt_2d *point, int clr)
// {
// 	char	*pixel;
// 	int		i;

// 	if (point->x < 1 || point->x >= mod->win_width)
// 		dbg_printf(no_block, "pixel x coordinate out of window");
// 	else if (point->y < 1 || point->y > mod->win_height)
// 		dbg_printf(no_block, "pixel y coordinate out of window");
// 	else
// 	{
// 		i = mod->img.bpp - 8;
// 		pixel = mod->img.addr + (point->y * mod->img.line_len + point->x
// 				* (mod->img.bpp / 8));
// 		while (i >= 0)
// 		{
// 			if (mod->img.endian != 0)
// 				*pixel++ = (clr >> i) & 0xFF;
// 			else
// 				*pixel++ = (clr >> (mod->img.bpp - 8 - i)) & 0xFF;
// 			i -= 8;
// 		}
// 	}
// }
