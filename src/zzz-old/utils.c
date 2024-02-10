/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:40:40 by astein            #+#    #+#             */
/*   Updated: 2024/02/07 08:39:38 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	ini_main(void)
{
	t_cub	cub;

	ini_cub(&cub);
	// parse map
	// if(!parse(&cub, av[1]))
	// {
	// 	ft_putstr_fd("Error\nInvalid map\n", STDERR_FILENO);
	// 	//exit (1);
	// }
	

	//Model

	//View
	
	return (cub);
}

void	config_main(t_cub *cub, char *path)
{
	//Model
	create_test_map_rectangle(cub);
	config_player(cub);
	ini_view(cub);
	ini_img_2d(cub, &cub->img_2d);
	ini_img_screen(cub, &cub->img_3d);
	ini_img_mini(cub, &cub->img_mini);
	ini_minimap(cub);
	ini_map2d(cub);
	update_model(cub);
	ini_vision(cub);

	//View
}

void angleToVector(double angleDegrees, t_vector_dbl *vector)
{
	// Adjust the angle since 0 degrees is north
	add_angle(&angleDegrees, -90);
	
    // Convert the adjusted angle to radians
    double angleRadians = angleDegrees * (M_PI / 180.0);
	// printf("roation in rad %f\n",angleRadians);

    // Calculate the normalized vector components
    vector->x = (double)cos(angleRadians);
    vector->y = (double)sin(angleRadians);
}

void add_angle(double *angle, double offset)
{
	// printf("angle before: %f ", *angle);
	*angle += offset;
	while(*angle >= 360)
		*angle -= 360;
	while(*angle < 0)
		*angle += 360;
	// printf("angle after: %f\n", *angle);
}
