/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:39 by astein            #+#    #+#             */
/*   Updated: 2024/01/30 13:04:27 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_main(t_cub *cub)
{
	// load window
	create_test_map(cub);
	ini_win(cub);
	ini_minimap(cub);
	ini_player(cub);
	ini_img(cub, &cub->img_ray);
	ini_img(cub, &cub->img_mini);

	// mlx hooks
	mlx_key_hook(cub->win.win, deal_key, cub);

	
	//mlx_hook(cub->win, B_CLS_WIN, 0, close_cubel, cub);
	//mlx_hook(window.win_ptr, DestroyNotify, KeyPressMask, ft_exit, all);

	
	// mlx loop
	eqip_imgs(cub);
	mlx_loop(cub->win.mlx);
}
