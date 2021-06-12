/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dlib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:36 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/12 02:31:21 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3DLIB_H
# define CUB3DLIB_H

# include "../../libft/libft.h"
# include "../../gnl/get_next_line_bonus.h"
# include "../../minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

# define KEY_UP					13
# define KEY_DOWN				1
# define KEY_RIGHT				2
# define KEY_LEFT				0

# define KEY_RIGHT_VISION		124
# define KEY_LEFT_VISION		123

# define ESC					53

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	int				up_switch;
	int				down_switch;
	int				left_switch;
	int				right_switch;
	int				color;
	int				arg;
}					t_data;
typedef	struct		s_map
{
	int				i;
	int				old;
	int				xpvu;
	char			**memoria;
	char			*ruta_sprite;
	char			*ruta_norte;
	char			*ruta_sur;
	char			*ruta_este;
	char			*ruta_oeste;
	int				w;
	int				h;
	int				color_f;
	int				color_c;
	char			*tmp1;
	char			*tmp2;
	int				bmp;
}					t_map;
typedef	struct		s_textura_norte
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_norte;
}					t_textura_norte;

typedef	struct		s_textura_sur
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_sur;
}					t_textura_sur;

typedef	struct		s_textura_este
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_este;
}					t_textura_este;

typedef	struct		s_textura_oeste
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_oeste;
}					t_textura_oeste;

typedef struct		s_sprite
{
	double			distance;
	int				num;
	int				tmp_num;
	int				*order;
	char			*sprites;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_add;
	unsigned int	*buffer;
	double			*z_buffer;
	int				tex_w;
	int				tex_h;
	double			x;
	double			y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_h;
	int				sprite_w;
	int				drawstart_x;
	int				drawend_x;
	int				drawstart_y;
	int				drawend_y;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				d;
}					t_sprite;

typedef struct		s_xysp
{
	double			rel;
	double			x;
	double			y;
}					t_xysp;

typedef struct		s_player
{
	char			nswe;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			olddirx;
	double			oldplanex;
	double			raydirx;
	double			raydiry;
	double			planex;
	double			planey;
	double			camerax;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				line_h;
	int				drawstart;
	int				drawend;
	double			movespeed;
	double			rotspeed;
	int				tex_w;
	int				tex_h;
	int				texnum;
	int				texx;
	int				texy;
	double			wallx;
	double			step;
	double			texpos;
	void			*textura;
	unsigned int	*buffer;

}					t_player;

typedef struct		s_keycode
{
	int				w;
	int				s;
	int				d;
	int				a;
	int				righ;
	int				left;
	int				esc;
}					t_keycode;

typedef	struct		s_cub3d
{
	t_data			data;
	t_player		player;
	t_textura_norte	textura_norte;
	t_textura_sur	textura_sur;
	t_textura_este	textura_este;
	t_textura_oeste	textura_oeste;
	t_map			map;
	t_sprite		sprite;
	t_xysp			*xysp;
	t_keycode		keycode;
}					t_cub3d;

void				my_mlx_pixel_put(t_cub3d *cub3d, int x, int y, int color);
int					key_move(t_cub3d *cub3d);
void				ft_get_tex_no_so(t_cub3d *cub3d);
void				ft_get_tex_we_ea(t_cub3d *cub3d);
void				ft_fill_texture(t_cub3d *cub3d);
void				ft_init_structs(t_cub3d *cub3d);
int					ft_control_error(int argc, char **argv);
void				error_cub3d(char *s);
int					ft_parseo(t_cub3d *cub3d, char **argv);
int					ft_check_lines(t_cub3d *cub3d, char *line);
void				ft_check_lines2(t_cub3d *cub3d, char *line, int i);
int					ft_check_resolucion(t_cub3d *cub3d, int x);
int					ft_is_space(char *line);
int					ft_check_ruta_norte(t_cub3d *cub3d, char *line);
int					ft_check_ruta_sur(t_cub3d *cub3d, char *line);
int					ft_check_ruta_este(t_cub3d *cub3d, char *line);
int					ft_check_ruta_oeste(t_cub3d *cub3d, char *line);
int					ft_check_ruta_sprite(t_cub3d *cub3d, char *line);
void				ft_check_color_f(t_cub3d *cub3d, char *line);
void				ft_check_color_c(t_cub3d *cub3d, char *line);
int					ft_rgb (char *r, char *g, char *b);
void				ft_check_map(t_cub3d *cub3d, char *line);
void				ft_reservar_map(t_cub3d *cub3d);
void				ft_fill_map(t_cub3d *cub3d, char **argv);
void				ft_check_memoria (t_cub3d *cub3d);
void				ft_flood_fill(t_cub3d *cub3d, int x, int y);
char				**ft_cpy_memory(t_cub3d *cub3d, char **mem);
void				ft_no_so(t_cub3d *cub3d);
void				ft_we_ea(t_cub3d *cub3d);
void				ft_free_var(char **color, char *tmp);
void				ft_res_sprites(t_cub3d *cub3d);
void				ft_sort_sprites(t_cub3d *cub3d);
void				ft_sprite(t_cub3d *cub3d);
void				ft_ray_sprite(t_cub3d *cub3d);
void				ft_ray_sprite_2(t_cub3d *cub3d);
void				ft_ray_sprite_3(t_cub3d *cub3d);
void				ft_ray_sprite_4(t_cub3d *cub3d, int y);
int					ft_screenshot(t_cub3d *cub3d);
void				ft_bit_rgb(unsigned char *s, int i);
void				ft_bmp_cabezera(t_cub3d *cub3d, int fd, int ps);
void				ft_free_matriz(t_cub3d *cub3d, char **matriz);
int					ft_exit(t_cub3d *cub3d);
int					ft_raycasting(t_cub3d *cub3d);
void				ft_raycasting_1(t_cub3d *cub3d);
void				ft_raycasting_2(t_cub3d *cub3d);
void				ft_raycasting_3(t_cub3d *cub3d);
void				ft_raycasting_4(t_cub3d *cub3d);
void				ft_draw_ray(t_cub3d *cub3d, int x);
void				ft_map(t_cub3d *cub3d);
void				ft_player_pos(t_cub3d *cub3d, char c, int j, int i);
int					ft_keypress(int key, t_cub3d *cub3d);
int					ft_keyrelease(int key, t_cub3d *cub3d);
void				ft_move_up_dowm (t_cub3d *cub3d);
void				ft_move_righ_left (t_cub3d *cub3d);
void				ft_rot_righ (t_cub3d *cub3d);
void				ft_rot_left(t_cub3d *cub3d);
#endif
