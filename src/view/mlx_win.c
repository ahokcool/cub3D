/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:39 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 18:02:31 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_win(t_win *win)
{
	win->mlx = NULL;
	win->mlx_win = NULL;
	win->win_height = -1;
	win->win_width = -1;
}

void	config_win(t_win *win)
{
	win->mlx = mlx_init();
	if (win->mlx == NULL)
	{
		perror("Error initializing mlx");
		exit(EXIT_FAILURE);
	}
	win->win_width = WIN_WIDTH;
	win->win_height = WIN_HEIGHT;
	win->mlx_win = mlx_new_window(win->mlx, win->win_width, win->win_height,
			"cub3D");
	if (win->mlx_win == NULL)
	{
		perror("Error creating window");
		exit(EXIT_FAILURE);
	}
}

void	destroy_win(t_win *win)
{
	if (win && win->mlx_win)
	{
		mlx_do_key_autorepeaton(win->mlx);
		mlx_destroy_window(win->mlx, win->mlx_win);
	}
	if (win)
	{
		win->mlx_win = NULL;
		win->mlx = NULL;
		win->win_height = -1;
		win->win_width = -1;
	}
}

void	start_loop(t_cub *cub)
{
	mlx_hook(cub->win.mlx_win, 17, 0, exit_game, cub);
	mlx_hook(cub->win.mlx_win, 2, (1L << 0), key_pressed, &cub->controller);
	mlx_hook(cub->win.mlx_win, 3, (1L << 1), key_released, &cub->controller);
	mlx_hook(cub->win.mlx_win, 6, (1L << 6), mouse_move, cub);
	mlx_mouse_hook(cub->win.mlx_win, mouse_click, cub);
	mlx_loop_hook(cub->win.mlx, model, cub);
	mlx_loop(cub->win.mlx);
}
