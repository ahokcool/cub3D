/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:00 by astein            #+#    #+#             */
/*   Updated: 2024/02/06 22:06:18 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	cub = NULL;
	ready_cub(&cub, &av[1]);
	if(!cub)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		exit (1);
	}

	// start the game loop (setting the hooks)
	mlx_start_loop(cub);
	free_cub(cub);
	cub = NULL;
	return (0);
}
