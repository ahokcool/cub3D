/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:39 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 11:06:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_win(t_win *win)
{
	win->mlx = NULL;
	win->win = NULL;
	win->win_height = -1;
	win->win_width = -1;
}

void	config_win(t_win *win)
{
	win->mlx = mlx_init();
	win->win_width = WIN_WIDTH;
	win->win_height = WIN_HEIGHT;
	win->win = mlx_new_window(win->mlx, win->win_width, win->win_height,
	"cub3D");
}

void	destroy_win(t_win *win)
{
	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	win->win = NULL;
	win->mlx = NULL;
	win->win_height = -1;
	win->win_width = -1;	
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







