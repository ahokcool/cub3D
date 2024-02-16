/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:21 by astein            #+#    #+#             */
/*   Updated: 2024/02/16 16:03:20 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft_printf.h"
# include "../mlx/mlx.h"
# include "config.h"
# include <stdbool.h>
# include <stdint.h> 

typedef struct s_clr
{
	double			red;
	double			green;
	double			blue;
}						t_clr;

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}			t_img;	

typedef struct s_win
{
	void			*mlx;
	void			*win;
	int				win_height;
	int				win_width;
}					t_win;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}						t_player;

typedef struct	s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
}	t_color;

typedef struct s_map_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	floor_clr;
	t_color ceiling_clr;
	char	**map;
}				t_map_config;

typedef struct s_cub
{
	t_win				win;
	t_img				img_ray;
	t_img				img_mini;
	t_map_config		map_config;
	t_player			player;
	bool				show_mini;
}						t_cub;

void	init_cub(t_cub *cub);
void	free_map(t_cub *cub);
bool 	parse(t_cub *cub, char *path);
void	mlx_main(t_cub *cub);
void	ini_win(t_cub *cub);
void	ini_img(t_cub *cub, t_img *img);
void	update_view(t_cub *cub);
int		deal_key(int key, t_cub *cub);
void 	eqip_imgs(t_cub *cub);

/*********************************** PARSING **********************************/

// utils
bool	check_format(char *path, char *expected_format);
bool	is_space(char c);
bool	file_exists(const char *path);
bool	is_line_empty(char *line);
void	replace_whitespaces(char *line);
bool    is_valid_map_char(char c);
bool	is_line_valid(char *line);
void    replace_spaces(char *line);
bool    validate_player(char *str);

bool	parse_textures_colors(t_cub *cub, int map_fd);
bool    parse_map(t_cub *cub, int cf_fd);
bool	handle_texture_line(t_cub *cub, char **parts, int *found);
bool	handle_color_line(t_cub *cub, char **parts, int *found);
bool    handle_map(t_cub *cub);

#endif
