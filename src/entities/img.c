/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:37 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 20:20:29 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	config_img_dim(t_cub *cub, t_img *img, t_vector_int *dimensions)
{
	printf("config_img_dim\n");
	size_t	img_size;

	if(dimensions)
	{
		img->width = dimensions->x;
		img->height = dimensions->y;
	}
	else
	{
		img->width = cub->win.win_width;
		img->height = cub->win.win_height;
	}

	img->mlx_img = mlx_new_image(cub->win.mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
			&(img->line_len), &(img->endian));
	img_size = img->width * img->height * sizeof(img->bpp);
	ft_bzero(img->addr, img_size);
}

void	config_img_file(t_cub *cub, t_img *img, char* path)
{
	img->mlx_img = mlx_xpm_file_to_image(cub->win.mlx, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
			&(img->line_len), &(img->endian));

	printf("config_img_file: loaded '%s' mlx img and addr are (%p, %p)\n", path, img->mlx_img, img->addr);
	printf("DETAILS: width: %d, height: %d, bpp: %d, line_len: %d, endian: %d\n", img->width, img->height, img->bpp, img->line_len, img->endian);
}

// void	config_img(void *mlx, t_img *img, char *path, t_vector_int *dimensions)
// {
// 	size_t	img_size;
	
// 	if (path)
// 	{
// 		printf("Loading image from path: %s\n", path);
// 		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &img->width,
// 				&img->height);
// 		if (img->mlx_img)
// 		{
// 			img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
// 					&(img->line_len), &(img->endian));
			
// 		}
// 	}
// 	else
// 	{
// 		if (dimensions)
// 		{
// 			printf("Loading empty image dimensions: (%d, %d)\n", dimensions->x, dimensions->y);
// 			img->mlx_img = mlx_new_image(mlx, dimensions->x, dimensions->y);
// 			if(img->mlx_img)
// 			{
// 				img->width = dimensions->x;
// 				img->height = dimensions->y;
// 			}
// 		}
// 		else
// 		{
// 			printf("Loading empty image dimensions: (%d, %d)\n", WIN_WIDTH, WIN_HEIGHT);
// 			img->mlx_img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
// 			if(img->mlx_img)
// 			{
// 				img->width = WIN_WIDTH;
// 				img->height = WIN_HEIGHT;
// 			}
// 		}
// 	}
// 	if (!img->mlx_img)
// 		printf("failed to load image!!\n");
// 	else
// 	{
// 		img_size = img->height * img->width * sizeof(img->bpp);
// 		// img_size = img->height * img->line_len;
// 		ft_bzero(img->addr, img_size);		
// 	}
// }

void	destroy_img(void *mlx, t_img *img)
{
	printf("destroying image at pointer %p\n", img);
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

void	put_tile(t_cub *cub, int x, int y, t_img *src, t_img *dest, int pixel_width)
{
	int	i;
	int	j;
	char *src_pxl;
	char *dst_pxl;
	
	(void)cub;
	i = 0;
	if (pixel_width == 0)
		pixel_width = src->width;
	while (i < pixel_width)
	{
		j = 0;
		while (j < pixel_width)
		{
			src_pxl = src->addr + (i * src->line_len + j * (src->bpp / 8));
			if ((y + i) < dest->height && (x + j) < dest->width)
			{
				dst_pxl = dest->addr + ((y + i) * dest->line_len + (x + j) * (dest->bpp / 8));
				// printf("current corordinates: (%d, %d) cur pxl: %p\n", x + j, y + i, dst_pxl);
				*(unsigned int*)dst_pxl = *(unsigned int*)src_pxl;
			}
			else
				printf("put_tile (%d, %d) out of bounds\n", x + j, y + i);
			j++;
		}
		i++;
	}	
}

void set_pixel_to_image(t_img *img, int x, int y, int color)
{
	char *dst_pxl;

	if (x < img->width && y < img->height)
	{
		if(x >= 0 && y >= 0 && x < img->width && y < img->height)
		{
			dst_pxl = img->addr + (y * img->line_len + x * (img->bpp / 8));
			// printf("current corordinates: (%d, %d) cur pxl: %p\n", x, y, dst_pxl);
			*(unsigned int*)dst_pxl = color;	
		}
	}
	// else
		// printf("set_pixel_to_image (%d, %d) out of bounds\n", x, y);
}

void draw_line(t_img *img, t_vector_dbl *start_coordinates, t_vector_dbl *vector_of_line, int color)
{
    double distance = sqrt(pow(vector_of_line->x, 2) + pow(vector_of_line->y, 2));
    double deltaX = vector_of_line->x / distance;
    double deltaY = vector_of_line->y / distance;
    double currentX = start_coordinates->x;
    double currentY = start_coordinates->y;

    for(double i = 0; i <= distance; i++)
    {
        set_pixel_to_image(img, (int)floor(currentX), (int)floor(currentY), color);
        currentX += deltaX;
        currentY += deltaY;
    }
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
