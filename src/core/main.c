/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:00 by astein            #+#    #+#             */
/*   Updated: 2024/02/20 17:04:53 by anshovah         ###   ########.fr       */
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
	
	// int i = -1;
	// while (cub.map_file.map[++i])
	// 	printf ("%s\n", cub.map_file.map[i]);
	// printf (" ---------------------- END TEST ---------------------- \n");
	// -------------------------------------------------------------------------
	
	// start the game
	if(!ready_cub(&cub, av[1]))
	{
		destroy_cub(&cub);
		exit (1);
	}

	// start the game loop (setting the hooks)
	start_loop(&cub);
	// destroy_cub(&cub);
	printf("main done\n");
	return (0);
}
