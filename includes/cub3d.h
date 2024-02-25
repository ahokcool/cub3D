/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:21 by astein            #+#    #+#             */
/*   Updated: 2024/02/25 18:49:55 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft_gnl_printf.h"
# include "../lib/minilibx-linux/mlx.h"
# include "config.h"
# include <stdbool.h>
# include <stdint.h> 

typedef struct s_clr
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
	int					line_l;
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
typedef struct s_map_file
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	floor_clr;
	t_color	ceiling_clr;
	int		rgb_floor;
	int		rgb_ceiling;
	char	**map;
}				t_map_file;

//PLAYER STRUCT
typedef struct s_player
{
	t_vector_dbl	pos;
	t_vector_dbl	dir;
	t_vector_dbl	v_plane;
	double			fov;
}					t_player;

typedef struct s_map2d
{
	t_img			img_wall;
	t_img			img_floor;
	char			**map_2d;
}						t_map2d;

typedef struct s_pxl_col
{
	double				perp_dist;
	int					height;
	char				hit_direction;
	t_vector_dbl		ray;
	t_vector_dbl		hit_pos;
	int					wall_start_y;
	int					wall_end_y;
	double				wall_x;
}	t_pxl_col;

typedef struct s_map3d
{
	t_pxl_col			cols[WIN_WIDTH];
	t_img				img_wall_no;
	t_img				img_wall_we;
	t_img				img_wall_so;
	t_img				img_wall_ea;
}	t_map3d;

typedef struct s_controller
{
	bool				move_forward;
	bool				move_backwards;
	bool				move_left;
	bool				move_right;
	bool				rotate_left;
	bool				rotate_right;
	bool				game_over;
	bool				show_3d;		
	bool				show_texture;	
	bool				mouse_rot;
}						t_controller;

typedef struct s_dda
{
	double			camera_x;
	t_vector_int	tile;
	t_vector_int	step;
	t_vector_dbl	side_dist;
	t_vector_dbl	d_dist;
	int				hit;
	int				side;
}					t_dda;

typedef struct s_draw_wall
{
	t_img			*text;
	t_img			*win;
	t_vector_dbl	text_pos;
	t_vector_int	win_pos;
	double			step;
	char			*text_pxl;
	char			*win_pxl;
	int				cur_win_y;
	double			cur_text_y;
}			t_draw_wall;

typedef struct s_cub
{
	t_win				win;
	t_img				img_2d;
	t_img				img_3d;
	t_map_file			map_file;
	t_player			player;
	t_map2d				map2d;
	t_map3d				map3d;
	t_controller		controller;
	bool				running;
}						t_cub;

//main.c
int		main(int ac, char **av);

// cub.c
bool	ready_cub(t_cub *cub, char *map_path);
int		destroy_cub(t_cub *cub);

//math.c
void	normalize_vector_dbl(t_vector_dbl *vector);
void	rotate_vector_dbl(t_vector_dbl *vector, double degrees);
void	rotate_vector_by_vector(t_vector_dbl *vector, t_vector_dbl *rotate);
int		create_rgb(int r, int g, int b);

//mlx_win.c
void	ini_win(t_win *win);
void	config_win(t_win *win);
void	destroy_win(t_win *win);
void	start_loop(t_cub *cub);

//img.c
void	ini_img(t_img *img);
void	config_img_dim(t_cub *cub, t_img *img, t_vector_int *dimensions);
void	config_img_file(t_cub *cub, t_img *img, char *path);
void	destroy_img(void *mlx, t_img *img);

//img_utils.c
void	put_tile(t_vector_int pos, t_img *src, t_img *dest);
void	set_pixel_to_image(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_vector_dbl *start_coordinates,
			t_vector_dbl *vector_of_line, int color);

//map.c
void	ini_map(t_cub *cub);
bool	config_map(t_cub *cub, char *map_path);
void	destroy_map(t_map_file *map);

//player.c
void	ini_player(t_player *player);
void	config_player(t_map_file *map_file, t_player *player);

// player_utils.c
void	player_move(t_player *player, t_controller *controller,
			t_map_file *map_file);
void	update_v_plane(t_player *player);
void	player_rotate(t_player *player, bool turn_right);

//column.c
void	ini_col(t_pxl_col *column);
void	config_col(t_pxl_col *col, t_player *player, t_map_file *map_file,
			int col_i);

//map2d.c
void	ini_map2d(t_map2d *map2d);
void	config_map2d(t_cub *cub, t_map2d *map2d);
void	destroy_map2d(void *mlx, t_map2d *map2d);

//map2d_utils.c
void	update_map2d_frame(t_cub *cub);

//map3d.c
void	ini_map3d(t_map3d *map3d);
void	config_map3d(t_cub *cub, t_map3d *map3d, t_player *player);
void	update_map3d(t_map3d *map3d, t_player *player, t_map_file *map_file);
void	update_map3d_frame(t_cub *cub);
void	destroy_map3d(void *mlx, t_map3d *map3d);

//draw_wall.c
void	draw_wall(t_cub *cub, int x_screen);

//controller.c
void	ini_controller(t_controller *controller);
int		key_pressed(int keycode, t_controller *controller);
int		key_released(int keycode, t_controller *controller);
int		mouse_click(int button, int x, int y, t_cub *cub);
int		mouse_move(int x, int y, t_cub *cub);

//model
int		model(void *void_cub);

//view.c
void	view(t_cub *cub);

// parsing
bool	parse(t_cub *cub, char *path);
bool	check_format(char *path, char *expected_format);
bool	is_space(char c);
bool	file_exists(const char *path);
bool	is_line_empty(char *line);
void	replace_whitespaces(char *line);
bool	is_valid_map_char(char c);
bool	is_line_valid(char *line);
void	replace_spaces(char *line);
bool	validate_player(char *str);

bool	parse_textures_colors(t_cub *cub, int map_fd);
bool	parse_map(t_cub *cub, int map_fd);
bool	handle_texture_line(t_cub *cub, char **parts, int *found);
bool	handle_color_line(t_cub *cub, char **parts, int *found);

#endif
