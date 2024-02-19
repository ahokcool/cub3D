/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:09:14 by astein            #+#    #+#             */
/*   Updated: 2024/01/29 19:13:31 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_map(char **map)
{
	(void)map;
	//flood fill or something
	return(false);
}

bool parse(t_cub *cub, char *path)
{
	(void)cub;
	(void)path;
	char * looong_str;
	//TODO:

	// open file
	// get next line
	
	// looooong str where u add the line via gnl and add a | at the end of each line
	// also count amount of lines
	// loop is done
	
	//looong_str = append_str(looong_str, line);
	//looong_str = append_str(looong_str, "|";
	
	// malloc maps first diminsion from the lines count
	// split by |
	// loop for each splt
	// malloc second diminsion from the length of the split
	
	// fill matrix

// 1 1 1 1 1 1 
// 1 1 1 1 1 1 1 1 1 
// 1 1 1 1 1 1 
// 1 1 1 1 1 1 1 1 1 1 1 1 1 
// 1 1 1 1 1 1 
// 1 1 1 1 1 1 

	
	// close file
	
	return (check_map(cub->map));
}
