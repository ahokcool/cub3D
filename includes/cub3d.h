/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:22:21 by astein            #+#    #+#             */
/*   Updated: 2024/01/30 13:17:21 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft_printf.h"
# include "../mlx/mlx.h"
# include "config.h"
# include <stdbool.h>

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
}						t_minimap;

typedef struct s_cub
{
	t_win				win;
	t_img				img_ray;
	t_img				img_mini;
	char				**map;
	t_player			player;
	t_minimap			minimap;
	bool				show_mini;
}						t_cub;

void	init_cub(t_cub *cub);
bool 	parse(t_cub *cub, char *path);
void	mlx_main(t_cub *cub);
void	ini_win(t_cub *cub);
void	ini_img(t_cub *cub, t_img *img);
void	update_view(t_cub *cub);
int		deal_key(int key, t_cub *cub);
void 	eqip_imgs(t_cub *cub);
void	dbg_put_minimap(t_cub *cub);
void	dbg_put_player(t_cub *cub);
void	ini_minimap(t_cub *cub);
void	ini_player(t_cub *cub);
void create_test_map(t_cub *cub);

#endif
