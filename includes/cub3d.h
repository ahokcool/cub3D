/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:21 by astein            #+#    #+#             */
/*   Updated: 2024/02/02 17:45:29 by astein           ###   ########.fr       */
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

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			rot_angle;
}						t_player;

typedef struct s_minimap
{
	t_img			wall;
	t_img			player_N;
	t_img			player_E;
	t_img			player_S;
	t_img			player_W;
	t_img			empty;
	char			*mini_map_str;
	int				map_border;
	int				x0;
	int				x1;
	int				y0;
	int				y1;
}						t_minimap;

typedef struct s_pnt_2d
{
	int					x;
	int					y;
}						t_pnt_2d;

typedef struct s_pnt_3d
{
	int					x;
	int					y;
	int					z;
}						t_pnt_3d;

typedef struct s_pnt_2_dbl
{
	double				x;
	double				y;
}						t_pnt_2d_dbl;

typedef struct s_raycast
{
	t_pnt_2d_dbl		v_direction;
	t_pnt_2d_dbl		v_plane;	
} 						t_raycast;

typedef struct s_cub
{
	t_win				win;
	t_img				img_ray;
	t_img				img_mini;
	char				**map;	//map[y][x]
	t_player			player;
	t_minimap			minimap;
	bool				show_mini;
	t_raycast			ray;
}						t_cub;

void	ini_cub(t_cub *cub);
bool 	parse(t_cub *cub, char *path);
void	mlx_main(t_cub *cub);
void	ini_view(t_cub *cub);
void	ini_img_screen(t_cub *cub, t_img *img);
void 	angleToVector(double angleDegrees, t_pnt_2d_dbl *vector);
void	ini_img_mini(t_cub *cub, t_img *img);
void	update_minimap_frame(t_cub *cub);
void	create_frame(t_cub *cub);
int		deal_key(int key, t_cub *cub);
void 	update_model(t_cub *cub);
void	dbg_put_minimap_big(t_cub *cub);
void	minimap_main(t_cub *cub);
void	dbg_put_player(t_cub *cub);
void	ini_minimap(t_cub *cub);
void	ini_player(t_cub *cub);
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

#endif
