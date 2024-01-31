/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:40:53 by astein            #+#    #+#             */
/*   Updated: 2024/01/30 15:44:13 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief   checks the key pressed and the roation of the player to know which way to walk
 * 
 * @param   cub         
 * @param   direction   
 * @return  char        
 */
static char	get_walk_direction(t_cub *cub, char direction)
{
	double delta_x;
	double delta_y;
	double radians;
	double move_angle;


	radians = cub->player.rot_angle * (M_PI / 180);
	delta_x = 0;
	delta_y = 0;
	if (direction == 'U')
		move_angle = 0;
	else if (direction == 'L')
		move_angle = M_PI / 2;
	else if (direction == 'D')
		move_angle = M_PI;
	else if (direction == 'R')
		move_angle = (-M_PI) / 2;
	else
		ft_putstr_fd("Error: Invalid direction\n", STDERR_FILENO);
	
	double effective_angle = radians + move_angle;
	printf("effective_angle: %f\n", effective_angle * (180 / M_PI));
	delta_x = cos(effective_angle);
    delta_y = sin(effective_angle);
	printf("delta_x: %f\n", delta_x);
	printf("delta_y: %f\n", delta_y);
	
	if (fabs(delta_x) > fabs(delta_y))
	{
		if (delta_x > 0)
			return ('E');
		else
			return ('W');
	}
	else
	{
		if (delta_y > 0)
			return ('S');	
		else
			return ('N');
	}
}

void ini_player(t_cub *cub)
{
	// get the index from the array of the player and set the pos_x and pos_y
	int	i;
	int j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' || cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
			{
				cub->player.pos_x = j;
				cub->player.pos_y = i;
				if (cub->map[i][j] == 'E')
					cub->player.rot_angle = 0;
				else if (cub->map[i][j] == 'N')
					cub->player.rot_angle = 90;
				else if (cub->map[i][j] == 'W')
					cub->player.rot_angle = 180;
				else if (cub->map[i][j] == 'S')
					cub->player.rot_angle = 270;
				cub->map[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
	write(1, "LEEEEEEEEEEE\n", 13);

}

void player_move(t_cub *cub, char direction)
{
	int x;
	int y;

	printf("direction: %c\n", direction);
	direction = get_walk_direction(cub, direction);
	printf("direction: %c\n", direction);

	x = cub->player.pos_x;
	y = cub->player.pos_y;
	if (direction == 'N')
		y--;
	else if (direction == 'W')
		x--;
	else if (direction == 'S')
		y++;
	else if (direction == 'E')
		x++;
	else
		ft_putstr_fd("Error: Invalid direction\n", STDERR_FILENO);
	if (x < 0 || y < 0)
		ft_putstr_fd("Error: Cant walk out of map!\n", STDERR_FILENO);
	else if (cub->map[y][x] == '1')
		ft_putstr_fd("Error: Invalid move (wall)\n", STDERR_FILENO);
	else
	{
		cub->player.pos_x = x;
		cub->player.pos_y = y;
	}
}