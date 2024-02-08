/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:21 by astein            #+#    #+#             */
/*   Updated: 2024/02/08 20:10:41 by astein           ###   ########.fr       */
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
	void			*mlx_win;
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
	t_vector_dbl	dir;	//player view direction
	t_vector_dbl	v_plane;
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
	t_img			img_wall;
	t_img			img_floor;
	char			**map_mini;
	int				size;	//4 = map size 4x4
	// int				map_border;
	// int				x0;
	// int				x1;
	// int				y0;
	// int				y1;
}						t_minimap;

typedef struct s_map2d
{
	t_img			img_wall;
	t_img			img_floor;
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
	int					height;
	char				hit_direction;	//N, S, E, W
	t_vector_dbl		ray;
	t_vector_dbl		hit_pos;
} 		t_pixel_column;
	
typedef struct s_map3d
{
	t_pixel_column		columns[WIN_WIDTH]; //ONE OBJECT FOR EACH PIXEL COLUMN (aka STRIPE)
} 						t_map3d;

typedef struct s_controller
{
	bool				move_forward;
	bool				move_backwards;
	bool				move_left;
	bool				move_right;
	bool				rotate_left;
	bool				rotate_right;
	bool				game_over;
	bool				show_3d;		//true=3d, false=2d
}						t_controller;

typedef struct s_cub
{
	//MLX DETAILS
	t_win				win;
	t_img				img_2d;		// Full 2D Map
	t_img				img_3d;		// 3D View / Raycast
	t_img				img_mini;	// Minimap (a few Tiles around the player)
	//MAP DETAILS
	t_map_config		map_config;
	//PLAYER DETAILS
	t_player			player;
	//RENDER DETAILS
	t_map2d				map2d;
	t_map3d				map3d;
	t_minimap			minimap;
	t_controller		controller;
	bool				running;
}						t_cub;

//main.c
int main(int ac, char **av);
int exit_game(t_cub *cub);

// cub.c
bool	ready_cub(t_cub *cub, char *map_path);
void	destroy_cub(t_cub *cub);

//math.c
void	normalize_vector_dbl(t_vector_dbl *vector);
void	rotate_vector_dbl(t_vector_dbl *vector, double degrees);
void	rotate_vector_by_vector(t_vector_dbl *vector, t_vector_dbl *rotate);


//mlx_win.c
void	ini_win(t_win *win);
void	config_win(t_win *win);
void	destroy_win(t_win *win);
void 	start_loop(t_cub *cub);

//img.c
void	ini_img(t_img *img);
// void	config_img(void *mlx, t_img *img, char *path, t_vector_int *dimensions);
// void	config_img_dim(void *mlx, t_img *img, t_vector_int *dimensions);
void	config_img_dim(t_cub *cub, t_img *img, t_vector_int *dimensions);
void	config_img_file(t_cub *cub, t_img *img, char* path);
void	put_tile(t_cub *cub, int x, int y, t_img *src, t_img *dest, int pixel_width);
void 	draw_line(t_img *img, t_vector_dbl *start_coordinates, t_vector_dbl *vector_of_line, int color);
void	set_pixel_to_image(t_img *img, int x, int y, int color);
void	destroy_img(void *mlx, t_img *img);

//map.c
void	ini_map(t_map_config *map);
void	config_map(t_map_config *map, char *map_path);
void	destroy_map(t_map_config *map);

//player.c
void	ini_player(t_player *player);
void	config_player(t_cub *cub, t_map_config *map_config, t_player *player);
void	destroy_player(void *mlx, t_player *player);
void 	player_move(t_player *player, t_controller *controller, t_map_config *map_config);
void 	player_rotate(t_player *player, bool turn_right);

//column.c
void	ini_column(t_pixel_column *column);
void	config_column(t_pixel_column *column);
void	destroy_column(t_pixel_column *column);
void	update_column(t_pixel_column *column, t_player *player, t_map_config *map_config, int column_index);

//miminmap.c
void	ini_minimap(t_minimap *minimap);
void	config_minimap(t_cub *cub, t_minimap *minimap, char **map);
void	destroy_minimap(void *mlx, t_minimap *minimap);
void	update_mapmini_frame(t_cub *cub);

//map2d.c
void	ini_map2d(t_map2d *map2d);
void	config_map2d(t_cub *cub, t_map2d *map2d);
void	destroy_map2d(void *mlx, t_map2d *map2d);
void	update_map2d_frame(t_cub *cub);

//map3d.c
void	ini_map3d(t_map3d *map3d);
void	config_map3d(t_map3d *map3d, t_player *player);
void	update_map3d(t_map3d *map3d, t_player *player, t_map_config *map_config);
void	update_map3d_frame(t_cub *cub);

//controller.c
void	ini_controller(void *mlx, t_controller *controller);
int		key_pressed(int keycode, t_controller *controller);
int		key_released(int keycode, t_controller *controller);
int		key_clicked(int keycode, t_cub *cub);
int		mouse_reader(int x, int y, t_player *player);
void	destroy_controller(void *mlx, t_controller *controller);

//model
int		model(void *void_cub);

//view.c
void	view(t_cub *cub);

//dbg.c
void create_test_map(t_map_config *map);
void	dbg_put_minimap_big(char **map);
void	dbg_put_player(t_player	*player);

//----------------------------------------------------------------------------
//OLD SHIT BELOW!!
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// void	ini_view(t_cub *cub);
// void	ini_img_screen(t_cub *cub, t_img *img);
// void	ini_img_mini(t_cub *cub, t_img *img);

// bool 	parse(t_cub *cub, char *path);
// void	mlx_main(t_cub *cub);
// void 	angleToVector(double angleDegrees, t_vector_dbl *vector);
// void	draw_rays(t_cub *cub);
// void	update_minimap_frame(t_cub *cub);
// void	calculate_rays(t_cub *cub);
// void	create_frame(t_cub *cub);
// int		deal_key(int key, t_cub *cub);
// int cread_keys(int key, t_cub *cub);
// void 	update_model(t_cub *cub);
// void	dbg_put_minimap_big(t_cub *cub);
// void	ini_player(t_player *player);
// void	minimap_main(t_cub *cub);
// void	dbg_put_player(t_cub *cub);
// t_cub	ini_main(void);
// void	config_main(t_cub *cub, char *path);
// void ini_model(t_cub *cub);
// int	get_player_pos(t_cub *cub, char format);
// void player_move(t_cub *cub, char direction);
// void	dbg_put_minimap_small(t_cub *cub);
// void	dbg_put_minimap_small(t_cub *cub);
// void create_test_map_rectangle(t_cub *cub);
// void	ini_vision(t_cub *cub);
// void	update_ray_frame(t_cub *cub);
// char	*player_cardinal_direction(t_cub *cub);
// void	ini_img_2d(t_cub *cub, t_img *img);
// void	put_tile(t_cub *cub, int x, int y, t_img *src, t_img *dest, int pixel_width);
// void	update_map2d_frame(t_cub *cub);
// void put_pixel_to_image(t_cub *cub, void *mlx_ptr, void *img_ptr, int x, int y, int color);
// void add_angle(double *angle, double offset);

#endif

