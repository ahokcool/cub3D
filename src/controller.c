/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:27:07 by astein            #+#    #+#             */
/*   Updated: 2024/01/29 19:24:04 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	turn(int key, t_cub *cub)
{
	// call a function that chanes the struct params of the player ( changing the model)
	//after changing the model we have to calculate the new images (ray and mini) and show them
	void eqip_imgs(t_cub *cub);
	
}

static void	move(int key, t_cub *cub)
{
	int		offset;

	offset = 5;
	// call a function that chanes the struct params of the player ( changing the model)
	//after changing the model we have to calculate the new images (ray and mini) and show them
	void eqip_imgs(t_cub *cub);
}

int	deal_key(int key, t_cub *cub)
{
	ft_putstr_fd("Key pressed: ", STDOUT_FILENO);
	if (key == K_ESC)
		exit(0); //TODO: CHANGE
	move(key, cub);
	turn(key, cub);
	return (0);
}
