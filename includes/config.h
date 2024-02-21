/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:18:47 by astein            #+#    #+#             */
/*   Updated: 2024/02/21 22:20:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

//KEYS
# define K_ESC 65307
# define K_ARROW_LEFT 65361
# define K_ARROW_UP 65362
# define K_ARROW_RIGHT 65363
# define K_ARROW_DOWN 65364

//RAY CASTING
# define WALL_HEIGHT 10

//RENDER DETAILS
# define MINIMAP_PIXEL_WIDTH 10
# define MINIMAP_BORDER_SIZE 2
# define MAP2D_PIXEL_WIDTH 20
# define TILE_SIZE 10

//MOVMENT DETAILS
# define MOVE_SPEED 0.008
# define ROT_SPEED 0.5

// COLORS WALLS
# define CLR_NORTH 	0x8A2BE2
# define CLR_SOUTH 	0x20B2AA
# define CLR_EAST 	0xFF6347
# define CLR_WEST 	0xFFD700

#endif