/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:21 by astein            #+#    #+#             */
/*   Updated: 2024/02/06 22:17:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft_printf.h"
# include "../mlx/mlx.h"
# include "config.h"
# include <stdbool.h>
# include <stdint.h>

//MLX STUFF
typedef struct	s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
}	t_color;

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}			t_img;	

typedef struct s_win
{
	void			*mlx;
	void			*win;
	int				win_height;
	int				win_width;
}					t_win;

//VECTORS STRUCT
typedef struct s_vector_int
{
	int					x;
	int					y;
}						t_vector_int;

typedef struct s_vector_dbl
{
	double				x;
	double				y;
}						t_vector_dbl;

//MAP STRUCT
typedef struct s_map_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	floor_clr;
	t_color ceiling_clr;
	char	**map;				//map[y][x]
}				t_map_config;

//PLAYER STRUCT
typedef struct s_player
{	
	t_vector_dbl	pos;	//player position
	t_vector_dbl	view;	//player view direction
	//Players Sprites for 2D map in different directions
	t_img			player_N;
	t_img			player_NE;
	t_img			player_E;
	t_img			player_SE;
	t_img			player_S;
	t_img			player_SW;
	t_img			player_W;
	t_img			player_NW;
}					t_player;

typedef struct s_minimap
{
	t_img			wall_tile;
	t_img			floor_tile;
	char			**map_mini;
	// int				map_border;
	// int				x0;
	// int				x1;
	// int				y0;
	// int				y1;
}						t_minimap;

typedef struct s_map2d
{
	t_img			wall_tile;
	t_img			floor_tile;
	char			**map_2d;	//map[y][x] //if the parsing changes the orriginal map, this will not be affected. e.g. spaces could be overritten to 1 which we dont want to display in the 2d Version
	// int				map_border;
	// int				x0;
	// int				x1;
	// int				y0;
	// int				y1;
}						t_map2d;

typedef struct s_pixel_column
{
	//For each Pixel (0->SCREEN WIDTH) we need to store the following information
	double				perp_distance_to_wall;
	double				height;
	char				hit_direction;	//N, S, E, W
	t_vector_dbl		hit_pos;
} 		t_pixel_column;
	
typedef struct s_raycast
{
	t_vector_dbl		v_direction;
	t_vector_dbl		v_plane;
	t_pixel_column		colums[WIN_WIDTH]; //ONE OBJECT FOR EACH PIXEL COLUMN (aka STRIPE)
} 						t_raycast;

typedef struct s_controller
{
	bool				move_up;
	bool				move_down;
	bool				move_left;
	bool				move_right;
	bool				rotate_left;
	bool				rotate_right;
}						t_controller;

typedef struct s_cub
{
	//MLX DETAILS
	t_win				win;
	t_img				img_ray;
	t_img				img_mini;
	t_img				img_2d;
	//MAP DETAILS
	t_map_config		map_config;
	//PLAYER DETAILS
	t_player			player;
	//RENDER DETAILS
	bool				show_mini;	//show / hide minimap
	bool				show_map2d;	//show / hide 2d map
	t_map2d				map2d;
	t_minimap			minimap;
	t_raycast			ray;
	t_controller		controller;	
}						t_cub;








//-----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void	ini_cub(t_cub *cub);
void	ini_view(t_cub *cub);
void	ini_img_screen(t_cub *cub, t_img *img);
void	ini_img_mini(t_cub *cub, t_img *img);

bool 	parse(t_cub *cub, char *path);
void	mlx_main(t_cub *cub);
void 	angleToVector(double angleDegrees, t_vector_dbl *vector);
void	draw_rays(t_cub *cub);
void	update_minimap_frame(t_cub *cub);
void	calculate_rays(t_cub *cub);
void	create_frame(t_cub *cub);
int		deal_key(int key, t_cub *cub);
int cread_keys(int key, t_cub *cub);
void 	update_model(t_cub *cub);
void	dbg_put_minimap_big(t_cub *cub);
void	ini_player(t_player *player);
void	minimap_main(t_cub *cub);
void	dbg_put_player(t_cub *cub);
void	ini_minimap(t_cub *cub);
void	config_player(t_cub *cub);
void create_test_map(t_cub *cub);
t_cub	ini_main(void);
void	config_main(t_cub *cub, char *path);
void ini_model(t_cub *cub);
int	get_player_pos(t_cub *cub, char format);
void player_move(t_cub *cub, char direction);
void	dbg_put_minimap_small(t_cub *cub);
void	dbg_put_minimap_small(t_cub *cub);
void create_test_map_rectangle(t_cub *cub);
void	ini_vision(t_cub *cub);
void	update_ray_frame(t_cub *cub);
char	*player_cardinal_direction(t_cub *cub);
void	ini_img_2d(t_cub *cub, t_img *img);
void	put_tile(t_cub *cub, int x, int y, t_img *src, t_img *dest, int pixel_width);
void	ini_map2d(t_cub *cub)	;
void	update_map2d_frame(t_cub *cub);
void put_pixel_to_image(t_cub *cub, void *mlx_ptr, void *img_ptr, int x, int y, int color);
void add_angle(double *angle, double offset);

#endif

