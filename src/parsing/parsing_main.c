/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/02/19 16:26:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Responsible for the whole process of parsing.
	First validates textures and colors and then the map
*/
bool	parse(t_cub *cub, char *path)
{
	char	*map_content;
	int		map_fd;

	if (!check_format(path, ".cub"))
		return (false);
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		return (false);
	if (!parse_textures_colors(cub, map_fd))
		return (false);
	if (!parse_map(cub, map_fd))
		return (false);
	close (map_fd);
	return (true);
}
