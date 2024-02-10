/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:27:07 by astein            #+#    #+#             */
/*   Updated: 2024/02/10 02:46:20 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_controller(t_controller *controller)
{
	controller->move_forward = false;
	controller->move_backwards = false;
	controller->move_left = false;
	controller->move_right = false;
	controller->rotate_left = false;
	controller->rotate_right = false;
	controller->game_over = false;
	controller->show_3d = false;
	controller->show_texture = false;
}

int key_pressed(int keycode, t_controller *controller)
{
	printf("Key pressed: %c\n", keycode);
	// only change the boolean values of the struct t_controller

	if (keycode == K_ESC)
		controller->game_over = true;
	else if (keycode == 'w')
		controller->move_forward = true;
	else if (keycode == 's')
		controller->move_backwards = true;
	else if (keycode == 'a')
		controller->move_left = true;
	else if (keycode == 'd')
		controller->move_right = true;
	else if (keycode == K_ARROW_LEFT || keycode == 'q')
		controller->rotate_left = true;
	else if (keycode == K_ARROW_RIGHT || keycode == 'e')
		controller->rotate_right = true;
	return (0);
}

int key_released(int keycode, t_controller *controller)
{
	printf("Key released: %c\n", keycode);
	if (keycode == 'w')
		controller->move_forward = false;
	else if (keycode == 's')
		controller->move_backwards = false;
	else if (keycode == 'a')
		controller->move_left = false;
	else if (keycode == 'd')
		controller->move_right = false;
	else if (keycode == K_ARROW_LEFT || keycode == 'q')
		controller->rotate_left = false;
	else if (keycode == K_ARROW_RIGHT || keycode == 'e')
		controller->rotate_right = false;
	else if(keycode == '2')
		controller->show_3d = false;
	else if(keycode == '3')
		controller->show_3d = true;
	else if(keycode == 't')
		controller->show_texture = !controller->show_texture;
	return (0);
}
int key_clicked(int keycode, t_cub *cub)
{
	printf("Key clicked: %c\n", keycode);
	if (keycode == K_ESC)
		exit_game(cub);
	// else if (keycode == '1')
	// 	cub->show_mini = !cub->show_mini;
	// else if (keycode == '2')
	// 	cub->show_map2d = !cub->show_map2d;

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

int	mouse_click(int button, int x, int y, t_cub *cub)
{
	printf("button %d, Mouse clicked: %d, %d\n", button, x, y);
	if (button == 4)
		cub->player.fov += 5;
	else if (button == 5)
		cub->player.fov -= 5;
	if (cub->player.fov < 50)
		cub->player.fov = 50;
	else if (cub->player.fov > 200)
		cub->player.fov = 200;
	
	
	printf("fov: %f\n", cub->player.fov);
	return (0);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	if(x > 2 * (WIN_WIDTH / 3))
		cub->controller.rotate_right = true;
	else if((x < WIN_WIDTH / 3))
		cub->controller.rotate_left = true;
	else
	{
		cub->controller.rotate_right = false;
		cub->controller.rotate_left = false;
	}
	printf("Mouse moved to: %d, %d\n", x, y);
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
