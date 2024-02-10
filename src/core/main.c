/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:00 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 12:58:11 by astein           ###   ########.fr       */
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

	// startup the game
	if(!ready_cub(&cub, av[1]))
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		exit (1);
	}

	// start the game loop (setting the hooks)
	start_loop(&cub);
	// destroy_cub(&cub);
	printf("main done\n");
	return (0);
}
