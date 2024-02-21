/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:26:53 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 18:03:30 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	view(t_cub *cub)
{
	if (cub->controller.show_3d)
		update_map3d_frame(cub);
	else
		update_map2d_frame(cub);
	if (cub->controller.show_3d)
		mlx_put_image_to_window(cub->win.mlx, cub->win.mlx_win,
			cub->img_3d.mlx_img, 0, 0);
	else
		mlx_put_image_to_window(cub->win.mlx, cub->win.mlx_win,
			cub->img_2d.mlx_img, 0, 0);
}
