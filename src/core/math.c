/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:51:57 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 14:59:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_vector_dbl(t_vector_dbl *vector)
{
	double	gcd;

	gcd = sqrt(vector->x * vector->x + vector->y * vector->y);
	vector->x /= gcd;
	vector->y /= gcd;
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