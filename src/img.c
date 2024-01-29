/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:37 by astein            #+#    #+#             */
/*   Updated: 2024/01/29 19:06:19 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_img(t_cub *cub, t_img *img)
{
	size_t	img_size;

	img->mlx_img = mlx_new_image(cub->win.mlx, cub->win.win_width, cub->win.win_height);
	img->addr = mlx_get_data_addr(img->mlx_img, &(img->bpp),
			&(img->line_len), &(img->endian));
	img_size = cub->win.win_height * cub->win.win_width * sizeof(img->bpp);
	ft_bzero(img->addr, img_size);
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
