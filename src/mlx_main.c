/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:39 by astein            #+#    #+#             */
/*   Updated: 2024/01/29 19:05:48 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_main(t_cub *cub)
{
	// load window
	ini_win(cub);
	ini_img(cub, &cub->img_ray);
	ini_img(cub, &cub->img_mini);

	// mlx hooks
	mlx_key_hook(cub->win.win, deal_key, cub);

	
	//mlx_hook(cub->win, B_CLS_WIN, 0, close_cubel, cub);
	//mlx_hook(window.win_ptr, DestroyNotify, KeyPressMask, ft_exit, all);

	
	// mlx loop
	//update_view(cub);
	mlx_loop(cub->win.mlx);
}
