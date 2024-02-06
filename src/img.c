/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:37 by astein            #+#    #+#             */
/*   Updated: 2024/02/05 14:41:22 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	render_next_img(t_cub *cub)
{
	//TODO:
}
