/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:52:12 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 16:29:27 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ini_map3d(t_map3d *map3d)
{
	int	i;
	
	i = -1;
	while (++i < WIN_WIDTH)
		ini_column(&map3d->columns[i]);
}

void	config_map3d(t_map3d *map3d, t_player *player)
{
	(void)map3d;
	(void)player;
}
