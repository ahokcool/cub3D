/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:43:08 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 17:34:13 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void create_test_map(t_map_file *map)
{
	int rows = 16; // Adjusted to match the actual data size
	int columns = 36; // Assuming this is the max length required including the null terminator
	char *data[] = {
		"11111111111111111111111111         ",
		"11111111111111111111111111         ",
		"10000N00001101111111000011         ",
		"101100000111011   11000011         ",
		"10010000000001111111000011111111111",
		"11111111101100000111000000000000111",
		"11111000001100000111011111111110111",
		"    1111011111111101110000001000111",
		"    1111011111111101110101001000111",
		"    1100000011010101110000000000111",
		"    1000000000000000110000001000111",
		"    1000000000000000000101001000111",
		"11110000011110000011110101101001111",
		"1111110111  1000001  10111101000111",
		"1111111111  1111111  11111111111111",
		"1111111111  1111111  11111111111111"
	};
	
	char **mat = (char **)malloc((rows + 1) * sizeof(char *));
	if (mat == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return; // Important to return or exit here
	}

	for (int i = 0; i < rows; i++) {
		mat[i] = (char *)malloc((columns + 1) * sizeof(char));
		strcpy(mat[i], data[i]);
	}
	mat[rows] = NULL; // Correctly use the variable instead of hardcoded value
	map->map = mat;
}
void	dbg_put_minimap_big(char **map)
{
	int	y;
	int x;
	
	y = 0;
	ft_putstr_fd("Map:\n", STDOUT_FILENO);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			// if(x == (int)(cub->player.pos_x) && y == (int)(cub->player.pos_y))
			// 	ft_putstr_fd(player_cardinal_direction(cub), STDOUT_FILENO);
			if(map[y][x] == '1')
				ft_putstr_fd("#", STDOUT_FILENO);
			else if(map[y][x] == '0')
				ft_putstr_fd(" ", STDOUT_FILENO);
			else
				ft_putchar_fd(map[y][x], STDOUT_FILENO);
			x++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		y++;
	}
}

void	dbg_put_player(t_player	*player)
{
	printf("------\n");
	printf("Player:\n");
	printf("position: (%f, %f)\n", player->pos.x, player->pos.y);
	printf("direction: (%f, %f)\n", player->dir.x, player->dir.y);
	printf("------\n");
}

//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// char	*player_cardinal_direction(t_cub *cub)
// {
// 		if (cub->player.rot_angle > 337.5 || cub->player.rot_angle <= 22.5)
// 	    return ("🡱"); // North
// 	else if (cub->player.rot_angle > 22.5 && cub->player.rot_angle <= 67.5)
// 	    return ("🡵"); // North-East
// 	else if (cub->player.rot_angle > 67.5 && cub->player.rot_angle <= 112.5)
// 	    return ("🡲"); // East
// 	else if (cub->player.rot_angle > 112.5 && cub->player.rot_angle <= 157.5)
// 	    return ("🡶"); // South-East
// 	else if (cub->player.rot_angle > 157.5 && cub->player.rot_angle <= 202.5)
// 	    return ("🡳"); // South
// 	else if (cub->player.rot_angle > 202.5 && cub->player.rot_angle <= 247.5)
// 	    return ("🡷"); // South-West
// 	else if (cub->player.rot_angle > 247.5 && cub->player.rot_angle <= 292.5)
// 	    return ("🡰"); // West
// 	else if (cub->player.rot_angle > 292.5 && cub->player.rot_angle <= 337.5)
// 	    return ("🡴"); // North-West
// 	return (" "); // This case may not be needed, assuming the rotation angle is always within 0-360 degrees
// }





// void	dbg_put_minimap_small(t_cub *cub)
// {
// 	int	i;

// 	i = 0;
// 	printf("----\n");
// 	while (cub->minimap.mini_map_str[i])
// 	{
// 		if (i % (2*MINIMAP_BORDER_SIZE+1) == 0)
// 			ft_putchar_fd('\n', STDOUT_FILENO);
// 		if(cub->minimap.mini_map_str[i] == '1')
// 			ft_putchar_fd('#', STDOUT_FILENO);
// 		else if(cub->minimap.mini_map_str[i] == 'P')
// 			ft_putchar_fd('P', STDOUT_FILENO);
// 		else
// 			ft_putchar_fd(' ', STDOUT_FILENO);
// 		i++;
// 	}	
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	printf("----\n");
// }

// /**
//  * @brief   1. Get Player Position
//  * 			2. Update Minimap String
//  * 			3. Print the String
//  * 
//  * @param   cub         
//  */
