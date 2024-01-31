/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:40:53 by astein            #+#    #+#             */
/*   Updated: 2024/01/31 17:57:00 by astein           ###   ########.fr       */
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
	 // Walking vectors for U, D, L, R
    double walk_vectors[4][2] = {
        {0, -1},  // U - forward
        {0, 1}, // D - backward
        {-1, 0}, // L - left
        {1, 0}   // R - right
    };

    int dir_index;
    if (direction == 'U') dir_index = 0;
    else if (direction == 'D') dir_index = 1;
    else if (direction == 'L') dir_index = 2;
    else if (direction == 'R') dir_index = 3;

    // Convert rotation angle to radians
    double rad = cub->player.rot_angle * (M_PI / 180.0);

    // Calculate the rotated walking vector
    double walk_x = walk_vectors[dir_index][0] * cos(rad) - walk_vectors[dir_index][1] * sin(rad);
    double walk_y = walk_vectors[dir_index][0] * sin(rad) + walk_vectors[dir_index][1] * cos(rad);

    // Update player's position if allowed
	// TODO: check if the player is walking into a wall
	cub->player.pos_x += walk_x;
	cub->player.pos_y += walk_y;
}

void ini_player(t_cub *cub)
{
	// get the index from the array of the player and set the pos_x and pos_y
	int	y;
	int x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
			{
				cub->player.pos_x = x * TILE_SIZE;
				cub->player.pos_y = y * TILE_SIZE;
				if (cub->map[y][x] == 'N')
					cub->player.rot_angle = 0;
				else if (cub->map[y][x] == 'E')
					cub->player.rot_angle = 90;
				else if (cub->map[y][x] == 'S')
					cub->player.rot_angle = 180;
				else if (cub->map[y][x] == 'W')
					cub->player.rot_angle = 270;
				cub->map[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
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

	// x = cub->player.pos_x;
	// y = cub->player.pos_y;
	// if (direction == 'N')
	// 	y--;
	// else if (direction == 'W')
	// 	x--;
	// else if (direction == 'S')
	// 	y++;
	// else if (direction == 'E')
	// 	x++;
	// else
	// 	ft_putstr_fd("Error: Invalid direction\n", STDERR_FILENO);
	// if (x < 0 || y < 0)
	// 	ft_putstr_fd("Error: Cant walk out of map!\n", STDERR_FILENO);
	// else if (cub->map[y][x] == '1')
	// 	ft_putstr_fd("Error: Invalid move (wall)\n", STDERR_FILENO);
	// else
	// {
	// 	cub->player.pos_x = x;
	// 	cub->player.pos_y = y;
	// }
}