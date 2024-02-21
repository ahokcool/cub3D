/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:16:46 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 20:56:45 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_tile(t_vector_int pos, t_img *src, t_img *dest)
{
	int		i;
	int		j;
	char	*src_pxl;
	char	*dst_pxl;
	int		pixel_width;

	i = 0;
	pixel_width = src->width;
	while (i < pixel_width)
	{
		j = 0;
		while (j < pixel_width)
		{
			src_pxl = src->addr + (i * src->line_l + j * (src->bpp / 8));
			if ((pos.y + i) < dest->height && (pos.x + j) < dest->width)
			{
				dst_pxl = dest->addr + ((pos.y + i) * dest->line_l
						+ (pos.x + j) * (dest->bpp / 8));
				*(unsigned int *)dst_pxl = *(unsigned int *)src_pxl;
			}
			j++;
		}
		i++;
	}
}

void	set_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*dst_pxl;

	if (x < img->width && y < img->height)
	{
		if (x >= 0 && y >= 0 && x < img->width && y < img->height)
		{
			dst_pxl = img->addr + (y * img->line_l + x * (img->bpp / 8));
			*(unsigned int *)dst_pxl = color;
		}
	}
}

void	draw_line(t_img *img, t_vector_dbl *start_coordinates,
		t_vector_dbl *vector_of_line, int color)
{
	double			distance;
	t_vector_dbl	delta;
	t_vector_dbl	cur;
	double			i;

	distance = sqrt(pow(vector_of_line->x, 2) + pow(vector_of_line->y, 2));
	delta.x = vector_of_line->x / distance;
	delta.y = vector_of_line->y / distance;
	cur.x = start_coordinates->x;
	cur.y = start_coordinates->y;
	i = 0;
	while (i <= distance)
	{
		set_pixel_to_image(img, (int)floor(cur.x), (int)floor(cur.y),
			color);
		cur.x += delta.x;
		cur.y += delta.y;
		i++;
	}
}
