/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:51:57 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 17:47:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_vector_dbl(t_vector_dbl *vector)
{
	double	gcd;

	gcd = sqrt(vector->x * vector->x + vector->y * vector->y);
	if(gcd != 0)
	{
		vector->x /= gcd;
		vector->y /= gcd;
	}
	else
	{
		vector->x = 0;
		vector->y = 0;
	}
}

void	rotate_vector_dbl(t_vector_dbl *vector, double degrees)
{
	double		radians;
	double		cosine;
	double		sine;
	double		x;
	double		y;

	radians = degrees * M_PI / 180;
	cosine = cos(radians);
	sine = sin(radians);
	x = vector->x;
	y = vector->y;
	vector->x = x * cosine - y * sine;
	vector->y = x * sine + y * cosine;
}

/**
 * @brief   Roatates the first vector by the angle of the second one
 * 
 */
void	rotate_vector_by_vector(t_vector_dbl *vector, t_vector_dbl *rotate)
{
	// Calculate the angle of rotation using the rotate vector
    double theta = atan2(rotate->y, rotate->x)+ M_PI / 2;

    // Calculate the new components of the vector after rotation
    double newX = vector->x * cos(theta) + vector->y * -sin(theta);
    double newY = -vector->x * -sin(theta) + vector->y * cos(theta);

    // Update the original vector with the new components
    vector->x = newX;
    vector->y = newY;
}