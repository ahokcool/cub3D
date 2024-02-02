/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:28:29 by astein            #+#    #+#             */
/*   Updated: 2024/02/02 16:18:13 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return (red << 16 | green << 8 | blue);
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
}


