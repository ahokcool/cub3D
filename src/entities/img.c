/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:37 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 21:44:46 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_l = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	config_img_dim(t_cub *cub, t_img *img, t_vector_int *dimensions)
{
	size_t	img_size;

	if (dimensions)
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
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp), &(img->line_l),
			&(img->endian));
	img_size = img->width * img->height * sizeof(img->bpp);
	ft_bzero(img->addr, img_size);
}

void	config_img_file(t_cub *cub, t_img *img, char *path)
{
	img->mlx_img = mlx_xpm_file_to_image(cub->win.mlx, path, &img->width,
			&img->height);
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp), &(img->line_l),
			&(img->endian));
}

void	destroy_img(void *mlx, t_img *img)
{
	// (void)mlx;
	printf("destroying image at pointer %p\n", img);
	if (mlx && img && img->mlx_img)
		mlx_destroy_image(mlx, img->mlx_img);
	if (img)
	{
		img->mlx_img = NULL;
		img->addr = NULL;
		img->bpp = -1;
		img->line_l = -1;
		img->endian = -1;
		img->width = -1;
		img->height = -1;
	}
}
