/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:27:07 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 13:06:23 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_controller(void *mlx, t_controller *controller)
{
	controller->move_up = false;
	controller->move_down = false;
	controller->move_left = false;
	controller->move_right = false;
	controller->rotate_left = false;
	controller->rotate_right = false;
	(void)mlx;
}

int key_pressed(int keycode, t_cub *cub)
{
	(void)cub;
	printf("Key pressed: %c\n", keycode);
	// only change the boolean values of the struct t_controller

	if (keycode == K_ESC)
		destroy_cub(cub);
	else if (keycode == 'w')
		cub->controller.move_up = true;
	else if (keycode == 's')
		cub->controller.move_down = true;
	else if (keycode == 'a')
		cub->controller.move_left = true;
	else if (keycode == 'd')
		cub->controller.move_right = true;
	else if (keycode == K_ARROW_LEFT)
		cub->controller.rotate_left = true;
	else if (keycode == K_ARROW_RIGHT)
		cub->controller.rotate_right = true;
	return (0);
}

int key_released(int keycode, t_cub *cub)
{
	(void)cub;
	printf("Key released: %d\n", keycode);
	// only change the boolean values of the struct t_controller
	return (0);
}

/**
 * @brief   THIS is the main controller of the game. it will be linked to the
 * 			mlx_key_hook and will be called every time a key is pressed or released
 * 
 * @param   key         
 * @param   cub         
 * @return  int         
 */

int	controller_mouse(int mouse_key, t_controller *controller)
{
	(void)mouse_key;
	(void)controller;
	//TODO: check if it needs to return int
	// only change the boolean values of the struct t_controller
	return (0);
}

void	destroy_controller(void *mlx, t_controller *controller)
{
	(void)controller;
	(void)mlx;
}



































//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// static void	turn(int key, t_cub *cub)
// {
// 	double	offset;

// 	offset = 10;
// 	// call a function that chanes the struct params of the player ( changing the model)
// 	//after changing the model we have to calculate the new images (ray and mini) and show them
// 	if (key == K_ARROW_LEFT)
// 	    cub->player.rot_angle -= offset;
// 	else if (key == K_ARROW_RIGHT)
// 	    cub->player.rot_angle += offset;
	
// 	// Correctly wrap the angle between 0 and 360 degrees
// 	if (cub->player.rot_angle >= 360)
// 	    cub->player.rot_angle -= 360;
// 	else if (cub->player.rot_angle < 0)
// 	    cub->player.rot_angle += 360;
	
// }

// static void	move(int key, t_cub *cub)
// {
// 	if (key == 'a')
// 		player_move(cub, 'L');
// 	else if (key == 'd')
// 		player_move(cub, 'R');
// 	else if (key == 'w')
// 		player_move(cub, 'U');
// 	else if (key == 's')
// 		player_move(cub, 'D');
		
// 	// call a function that chanes the struct params of the player ( changing the model)
// 	//after changing the model we have to calculate the new images (ray and mini) and show them
// }

// int cread_keys(int key, t_cub *cub)
// {
// 	// ft_putstr_fd("Key down: ", STDOUT_FILENO);
// 	move(key, cub);
	
// 	update_model(cub);
// 	return (0);
// }

// int	deal_key(int key, t_cub *cub)
// {
// 	// ft_putstr_fd("Key pressed: ", STDOUT_FILENO);
// 	// ft_putchar_fd(key, STDOUT_FILENO);
// 	// ft_putchar_fd('\n', STDOUT_FILENO);
// 	if (key == K_ESC)
// 		exit(0); //TODO: CHANGE
// 	if (key == 'm')
// 		cub->show_mini = !cub->show_mini;
// 	if (key == '2')
// 		cub->show_map2d = !cub->show_map2d;
// 	turn(key, cub);
// 	update_model(cub);
// 	return (0);
// }
