/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:00 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 18:13:31 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_cub cub;

	// check args
	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", STDERR_FILENO);
		exit (1);
	}

	// startup the game
	if(!ready_cub(&cub, av[1]))
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		exit (1);
	}

	// start the game loop (setting the hooks)
	put_tile(&cub, 0, 0, &cub.minimap.img_floor, &cub.img_3d, 10);
	mlx_pixel_put(cub.win.mlx, cub.win.mlx_win, 10, 10, 0x00FF0000);
	mlx_put_image_to_window(cub.win.mlx, cub.win.mlx_win, cub.img_3d.mlx_img, 10, 10);
	start_loop(&cub);
	// destroy_cub(&cub);
	printf("main done\n");
	return (0);
}
