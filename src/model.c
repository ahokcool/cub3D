/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:26:36 by astein            #+#    #+#             */
/*   Updated: 2024/01/29 19:26:07 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void   equip_ray_img(t_cub *cub)
{
	// calculate the current view and draw it to the img
}

static void   equip_mini_img(t_cub *cub)
{
	// calculate the current view and draw it to the img
}

void eqip_imgs(t_cub *cub)
{
	equip_ray_img(cub);
	if(cub->show_mini)
		equip_mini_img(cub);
	update_view(cub);
}