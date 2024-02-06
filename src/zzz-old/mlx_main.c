/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:18:39 by astein            #+#    #+#             */
/*   Updated: 2024/02/06 22:05:09 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_start_loop(cub)
{
	mlx_key_hook(cub.win.win, deal_key, &cub);
	//TODO: add hook for key release
	mlx_hook(cub.win.win, 02, (1L << 0), cread_keys, &cub);
	//TODO: add hook for mouse movement
	//TODO: THE CALCULATION OF THE NEXT FRAME SHOULD BE DONE IN THE LOOP HOOK NOT IN THE KEY HOOK!	e.g. mlx_loop_hook(cub.win.mlx, update_frame, &cub);
	mlx_loop(cub.win.mlx);	
}







