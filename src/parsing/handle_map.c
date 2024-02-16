/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:19:15 by anshovah          #+#    #+#             */
/*   Updated: 2024/02/16 19:57:49 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void  treat_begin_spaces(t_cub *cub)
{
   int   i;
   int   len;
   char  *temp;

   // if (cub->map_config.map[0][0] != ' ')
   //    return ;
   // i = -1;
   // while (cub->map_config.map[++i])
   // {
   //    if (cub->map_config.map[i] && cub->map_config.map[i][0] != ' ')
   //       return ;
   // }
   // i = -1;
   // len = 0;
   // while (cub->map_config.map[0][len])
   //    len++;
}

bool    handle_map(t_cub *cub)
{
   treat_begin_spaces(cub);
}