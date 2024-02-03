/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/02/03 16:43:47 by anshovah         ###   ########.fr       */
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
	
	/*
		!!!!!!!!!!!!! HEY Johnny !!!!!!!!!!!!!
		Here's info for you
		* you have a file descriptor and the file starts right after I found all the components.
		you need to skip the empty lines and free them, u can use my function "is_line_empty"
		* I did memory cleanup for my stuff and normineted it, also I restructured all the stuff here
		* name you function something like "parse_map" and create a file for it, call that function
		 from here. let's keep this file clean
		* don't forget to close a file descriptor
		* I wrote comments for all my functions
	*/
	
	return (false); // by default this function always returns false so the fucking window is not open
}
