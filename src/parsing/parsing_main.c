/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/02/10 22:36:41 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Responsible for the whole process of parsing.
	First validates textures and colors and then the map
*/
bool parse(t_cub *cub, char *path)
{
	char	*map_content;
	int		cf_fd;

	if (!check_format(path, ".cub"))
		return (false);
	cf_fd = open(path, O_RDONLY);
	if (cf_fd < 0)
		return (false);
	if (!parse_textures_colors(cub, cf_fd))
		return (false);
	if (!parse_map(cub, cf_fd))
		return (false);
	return (false); // by default this function always returns false so the fucking window is not open
}
