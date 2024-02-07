/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:27:07 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 10:56:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_controller(t_controller *controller)
{
	controller->move_up = false;
	controller->move_down = false;
	controller->move_left = false;
	controller->move_right = false;
	controller->rotate_left = false;
	controller->rotate_right = false;
}

/**
 * @brief   THIS is the main controller of the game. it will be linked to the
 * 			mlx_key_hook and will be called every time a key is pressed or released
 * 
 * @param   key         
 * @param   cub         
 * @return  int         
 */
int	controller_keys(int key, t_controller *controller)
{
	// only change the boolean values of the struct t_controller
}

int	controller_mouse(int mouse_key, t_controller *controller)
{
	//TODO: check if it needs to return int
	// only change the boolean values of the struct t_controller
}





































//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void	turn(int key, t_cub *cub)
{
	double	offset;

	offset = 10;
	// call a function that chanes the struct params of the player ( changing the model)
	//after changing the model we have to calculate the new images (ray and mini) and show them
	if (key == K_ARROW_LEFT)
	    cub->player.rot_angle -= offset;
	else if (key == K_ARROW_RIGHT)
	    cub->player.rot_angle += offset;
	
	// Correctly wrap the angle between 0 and 360 degrees
	if (cub->player.rot_angle >= 360)
	    cub->player.rot_angle -= 360;
	else if (cub->player.rot_angle < 0)
	    cub->player.rot_angle += 360;
	
}

static void	move(int key, t_cub *cub)
{
	if (key == 'a')
		player_move(cub, 'L');
	else if (key == 'd')
		player_move(cub, 'R');
	else if (key == 'w')
		player_move(cub, 'U');
	else if (key == 's')
		player_move(cub, 'D');
		
	// call a function that chanes the struct params of the player ( changing the model)
	//after changing the model we have to calculate the new images (ray and mini) and show them
}

int cread_keys(int key, t_cub *cub)
{
	// ft_putstr_fd("Key down: ", STDOUT_FILENO);
	move(key, cub);
	
	update_model(cub);
	return (0);
}

int	deal_key(int key, t_cub *cub)
{
	// ft_putstr_fd("Key pressed: ", STDOUT_FILENO);
	// ft_putchar_fd(key, STDOUT_FILENO);
	// ft_putchar_fd('\n', STDOUT_FILENO);
	if (key == K_ESC)
		exit(0); //TODO: CHANGE
	if (key == 'm')
		cub->show_mini = !cub->show_mini;
	if (key == '2')
		cub->show_map2d = !cub->show_map2d;
	turn(key, cub);
	update_model(cub);
	return (0);
}
