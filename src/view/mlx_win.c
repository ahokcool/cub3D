/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:39 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 14:10:26 by astein           ###   ########.fr       */
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
	// int	screen_width;
	// int	screen_height;

	// screen_width = 0;
	// screen_height = 0;
	win->mlx = mlx_init();
	if (win->mlx == NULL)
	{
		perror("Error initializing mlx");
		exit(EXIT_FAILURE); // or any other error handling strategy
	}
	// mlx_get_screen_size(win->mlx, &screen_width, &screen_height);
	win->win_width = WIN_WIDTH;
	win->win_height = WIN_HEIGHT;
	win->mlx_win = mlx_new_window(win->mlx, win->win_width, win->win_height, "cub3D");
	if (win->mlx_win == NULL)
	{
		perror("Error creating window");
		exit(EXIT_FAILURE); // or any other error handling strategy
	}
	// mlx_do_key_autorepeatoff(win->mlx);
}

void	destroy_win(t_win *win)
{
	mlx_do_key_autorepeaton(win->mlx);
	if (win->mlx_win)
		mlx_destroy_window(win->mlx, win->mlx_win);
	win->mlx_win = NULL;
	win->mlx = NULL;
	win->win_height = -1;
	win->win_width = -1;
}

void start_loop(t_cub *cub)
{
	mlx_hook(cub->win.mlx_win, 17, 0, exit_game, &cub);
	mlx_hook(cub->win.mlx_win, 2, (1L << 0), key_pressed, &cub->controller);
	mlx_hook(cub->win.mlx_win, 3, (1L << 1), key_released, &cub->controller);
	mlx_hook(cub->win.mlx_win, 6, (1L << 6), mouse_reader, &cub->controller);
	mlx_key_hook(cub->win.mlx_win, key_clicked, cub);
	mlx_loop_hook(cub->win.mlx, model, cub);
	mlx_loop(cub->win.mlx);
}


//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


// void	mlx_start_loop(cub)
// {
// 	mlx_key_hook(cub.win.win, deal_key, &cub);
// 	//TODO: add hook for key release
// 	mlx_hook(cub.win.win, 02, (1L << 0), cread_keys, &cub);
// 	//TODO: add hook for mouse movement
// 	//TODO: THE CALCULATION OF THE NEXT FRAME SHOULD BE DONE IN THE LOOP HOOK NOT IN THE KEY HOOK!	e.g. mlx_loop_hook(cub.win.mlx, update_frame, &cub);
// 	mlx_loop(cub.win.mlx);	
// }







