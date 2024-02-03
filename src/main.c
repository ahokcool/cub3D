/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:00 by astein            #+#    #+#             */
/*   Updated: 2024/02/03 15:51:50 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_cub cub;

	ft_putendl_fd("Lets gooooo!", STDOUT_FILENO);
	
	// check args
	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", STDERR_FILENO);
		exit (1);
	}
	
	init_cub(&cub);
	
	// parse map
	if(!parse(&cub, av[1]))
	{
		ft_putstr_fd("Error\nInvalid map\n", STDERR_FILENO);
		free_map(&cub);
		exit (1);
	}
	
	//start mlx
	mlx_main(&cub);

	return (0);
}
