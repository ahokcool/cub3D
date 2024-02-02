/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:43:08 by astein            #+#    #+#             */
/*   Updated: 2024/02/02 17:50:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*player_cardinal_direction(t_cub *cub)
{
		if (cub->player.rot_angle > 337.5 || cub->player.rot_angle <= 22.5)
	    return ("🡱"); // North
	else if (cub->player.rot_angle > 22.5 && cub->player.rot_angle <= 67.5)
	    return ("🡵"); // North-East
	else if (cub->player.rot_angle > 67.5 && cub->player.rot_angle <= 112.5)
	    return ("🡲"); // East
	else if (cub->player.rot_angle > 112.5 && cub->player.rot_angle <= 157.5)
	    return ("🡶"); // South-East
	else if (cub->player.rot_angle > 157.5 && cub->player.rot_angle <= 202.5)
	    return ("🡳"); // South
	else if (cub->player.rot_angle > 202.5 && cub->player.rot_angle <= 247.5)
	    return ("🡷"); // South-West
	else if (cub->player.rot_angle > 247.5 && cub->player.rot_angle <= 292.5)
	    return ("🡰"); // West
	else if (cub->player.rot_angle > 292.5 && cub->player.rot_angle <= 337.5)
	    return ("🡴"); // North-West
	return (" "); // This case may not be needed, assuming the rotation angle is always within 0-360 degrees
}
void	dbg_put_player(t_cub *cub)
{
	printf("------\n");
	printf("Player:\n");
	printf("pos_x: %f\n", cub->player.pos_x);
	printf("pos_y: %f\n", cub->player.pos_y);
	printf("rot_angle: %f\n", cub->player.rot_angle);
	printf("------\n");
}

void	dbg_put_minimap_big(t_cub *cub)
{
	int	y;
	int x;
	
	y = 0;
	ft_putstr_fd("Map:\n", STDOUT_FILENO);
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if(x == (int)(cub->player.pos_x) && y == (int)(cub->player.pos_y))
				ft_putstr_fd(player_cardinal_direction(cub), STDOUT_FILENO);
			else if(cub->map[y][x] == '1')
				ft_putstr_fd("#", STDOUT_FILENO);
			else if(cub->map[y][x] == '0')
				ft_putstr_fd(" ", STDOUT_FILENO);
			else
				ft_putchar_fd(cub->map[y][x], STDOUT_FILENO);
			x++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		y++;
	}
}

void create_test_map(t_cub *cub)
{
	int rows = 14;
    int columns = 50; // Not including the null terminator
    char *data[] = {
        "        1111111111111111111111111",
        "        1000000000110111111100001",
        "        10110N000111011   1100001",
        "        1001000000000111111100001",
        "111111111011000001110000000000001",
        "100000000011000001110111111111111",
        "11110111111111011100000010001",
        "11110111111111011101010010001",
        "11000000110101011100000000001",
        "10000000000000001100000010001",
        "10000000000000000001010010001",
        "1100000111100000111111011110011",
        "11110111  1000001  101111010001",
        "11111111  1111111  111111111111"
    };
    // Allocate memory for rows
    char **mat = (char **)malloc((rows+1) * sizeof(char *));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    }

    // Allocate memory for columns and copy data
    for (int i = 0; i < rows; i++) {
        mat[i] = (char *)malloc((columns + 1) * sizeof(char)); // +1 for null terminator
        if (mat[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d\n", i);
            // Free already allocated memory
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
        }
        strcpy(mat[i], data[i]);
    }
	mat[14] = NULL;
	cub->map = mat;
	
	int x;
	int y;
	ft_matrix_dim(cub->map, &x, &y);
	printf("x: %d\ny: %d\n", x, y);
}

void create_test_map_rectangle(t_cub *cub)
{
	int rows = 14;
    int columns = 50; // Not including the null terminator
    char *data[] = {
        "        1111111111111111111111111",
        "        1000000000110111111100001",
        "        10110N000111011   1100001",
        "        1001000000000111111100001",
        "111111111011000001110000000000001",
        "100000000011000001110111111111111",
        "    11110111111111011100000010001",
        "    11110111111111011101010010001",
        "    11000000110101011100000000001",
        "    10000000000000001100000010001",
        "    10000000000000000001010010001",
        "111100000111100000111111011110011",
        "1111110111  1000001  101111010001",
        "1111111111  1111111  111111111111"
    };
    // Allocate memory for rows
    char **mat = (char **)malloc((rows+1) * sizeof(char *));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    }

    // Allocate memory for columns and copy data
    for (int i = 0; i < rows; i++) {
        mat[i] = (char *)malloc((columns + 1) * sizeof(char)); // +1 for null terminator
        if (mat[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d\n", i);
            // Free already allocated memory
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
        }
        strcpy(mat[i], data[i]);
    }
	mat[14] = NULL;
	cub->map = mat;
	
	int x;
	int y;
	ft_matrix_dim(cub->map, &x, &y);
	printf("x: %d\ny: %d\n", x, y);
}


void	dbg_put_minimap_small(t_cub *cub)
{
	int	i;

	i = 0;
	printf("----\n");
	while (cub->minimap.mini_map_str[i])
	{
		if (i % (2*MINIMAP_BORDER_SIZE+1) == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		if(cub->minimap.mini_map_str[i] == '1')
			ft_putchar_fd('#', STDOUT_FILENO);
		else if(cub->minimap.mini_map_str[i] == 'P')
			ft_putchar_fd('P', STDOUT_FILENO);
		else
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}	
	ft_putchar_fd('\n', STDOUT_FILENO);
	printf("----\n");
}

/**
 * @brief   1. Get Player Position
 * 			2. Update Minimap String
 * 			3. Print the String
 * 
 * @param   cub         
 */
