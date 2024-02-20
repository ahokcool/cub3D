/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:00 by astein            #+#    #+#             */
/*   Updated: 2024/02/20 15:50:56 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int exit_game(t_cub *cub)
{
	destroy_cub(cub);
	exit(0);
}

int main(int ac, char **av)
{
	t_cub cub;

	// check args
	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", STDERR_FILENO);
		exit (1);
	}
	// ini_cub(&cub);
	// parse map
	
	/* -------------------------------- TEST -------------------------------- */
	// printf (" ---------------------- START TEST ---------------------- \n");
	// printf ("TEXTURES: \n NO - %s\n SO - %s\n WE - %s\n EA - %s\n", 
	// 	cub.map_file.no_texture, cub.map_file.so_texture,
	// 	cub.map_file.we_texture, cub.map_file.ea_texture);
	// printf ("COLORS: \n Floor: \n Red - %d\n Green - %d\n Blue - %d\n \
	// 				 \n Ceiling: \n Red - %d\n Green - %d\n Blue - %d\n",
	// 		cub.map_file.floor_clr.red, cub.map_file.floor_clr.green, cub.map_file.floor_clr.blue,
	// 		cub.map_file.ceiling_clr.red, cub.map_file.ceiling_clr.green, cub.map_file.ceiling_clr.blue);
	
	// int i = -1;
	// while (cub.map_file.map[++i])
	// 	printf ("%s\n", cub.map_file.map[i]);
	// printf (" ---------------------- END TEST ---------------------- \n");
	// -------------------------------------------------------------------------
	
	// start the game
	if(!ready_cub(&cub, av[1]))
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		destroy_cub(&cub);
		exit (1);
	}

	// start the game loop (setting the hooks)
	start_loop(&cub);
	// destroy_cub(&cub);
	printf("main done\n");
	return (0);
}
