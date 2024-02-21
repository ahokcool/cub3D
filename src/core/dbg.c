/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:43:08 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 18:00:52 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dbg_put_player(t_player *player)
{
	printf("------\n");
	printf("Player:\n");
	printf("position: (%f, %f)\n", player->pos.x, player->pos.y);
	printf("direction: (%f, %f)\n", player->dir.x, player->dir.y);
	printf("------\n");
}
