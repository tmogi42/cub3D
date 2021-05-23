/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:23:56 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:23:56 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BUFFER_SIZE 210

typedef struct s_map
{
	int		res[2];
	char	*(t_path[5]);
	int		rgb[3];
	int		c;
	int		f_color;
	int		c_color;
	int		max_width;
	int		height;
	char	**map;
	char	**tmpmap;
}	t_map;

typedef struct s_wall
{
	double	camerax;
	double	rdirx;
	double	rdiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perp;
	double	wallx;
	double	step;
	int		mapx;
	int		mapy;
	int		texx;
	int		texy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		l_height;
	int		draw_s;
	int		draw_e;
}	t_wall;

typedef struct s_sprite
{
	int		num;
	double	*x;
	double	*y;
	int		*order;
	double	*dist;
	double	distx;
	double	disty;
	double	sp_x;
	double	sp_y;
	double	inv_d;
	double	tf_x;
	double	tf_y;
	int		s_x;
	int		height;
	int		width;
	int		draw_sx;
	int		draw_sy;
	int		draw_ex;
	int		draw_ey;
	int		texx;
	int		texy;
}	t_sprite;

typedef struct s_bmp
{
	int				fd;
	unsigned long	filesize;
	unsigned long	offset;
	unsigned long	header_size;
	unsigned long	no_val;
	unsigned long	data_size;
	unsigned long	width;
	unsigned long	height;
	unsigned int	planes;
	unsigned int	color;
	int				real_width;
	unsigned char	*rgb;
}	t_bmp;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		l_s;
	int		e;
	int		texnum;
	int		w[5];
	int		r_w[5];
	int		h[5];
}	t_img;

typedef struct s_info
{
	t_map		map;
	t_img		img;
	t_sprite	sp;
	t_bmp		bmp;
	void		*mlx;
	void		*win;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		cp_x;
	double		cp_y;
	double		movespeed;
	double		rotspeed;
	double		*zbuf;
	int			valid_count;
	int			s_w;
	int			s_h;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_esc;
	int			key_ar_l;
	int			key_ar_r;
	int			**buf;
	int			**tex;
}	t_info;

int		main_loop(t_info *info);
int		start_game(t_info *info);
void	move_player(t_info *info, int lr_flag, int p_or_m);
void	rotate_player(t_info *info, int p_or_m);
int		free_all(char **line, char **buf, char **tmp, int result);
int		free_members(t_info *info);
int		free_char_arr(char ***str, int start, int end);
int		free_int_arr(int ***str, int start, int end);
int		check_read_data(t_info *info);
int		is_map_closed(t_info *info, t_map *map);
void	convert_map(t_map *map);
int		floodfill(char **map, int x, int y, int flag);
int		error(int fd, int result, t_info *info);
int		check_file_name(char *val);
int		judge_input_args(int argc, char **argv);
int		check_color_val(t_map *map);
int		check_start_zero(char *line);
int		init_params(t_info *info);
void	init_map_data(t_info *info);
void	init_info_data(t_info *info);
char	set_player_pos(t_info *info);
void	set_player_dir(char p_dir, t_info *info);
size_t	search_newline(char *buf, size_t *i);
size_t	gnl_strlen(char *str);
int		gnl_read(int fd, char **line, char **tmp, int *newline_flag);
char	*gnl_strdup(char **src, size_t newl_p);
char	*ft_strdup(char *dest);
int		gnl_strjoin(char **line, char *src, size_t n);
int		get_line_from_tmp(char **line, char **tmp);
int		get_next_line(int fd, char **line, char **tmp);
int		read_cub_file(int fd, t_info *info);
int		get_identifier_info(char *line, t_info *info);
int		check_identifier(char *line, t_info *info);
int		get_resolution(char *line, t_info *info, int i);
int		get_texture_path(char *line, t_info *info, int num);
int		get_color(char *line, t_map *map, int *color);
int		convert_color(int *color, int *val);
int		read_map(char *line, t_info *info);
int		copy_map_to_tmp(t_info *info);
int		is_valid_size(t_info *info, char *line);
int		ft_strlen(char *str);
int		ft_strcmp(char *str1, char *str2);
int		ft_chrstr(char c, char *str);
int		ft_strstr(char *str1, char *str2);
int		check_only_space(char *line);
void	draw_floor_and_ceiling(t_info *info);
void	draw_wall(t_wall *wall, t_info *info, int x);
void	draw_sprite(t_info *info, t_sprite *sp, t_img *img, int x);
void	draw_image(t_info *info, t_img *img);
void	key_update(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
int		safe_shutdown(t_info *info);
void	clear_all_params(t_info *info);
void	copy_texture_color(t_img *img, int **tex, int num);
int		load_image(t_info *info, int **tex, char *path, t_img *im);
int		load_texture(t_info *info, t_map *map);
int		allocate_buf_area(t_info *info);
void	calc_casting(t_info *info);
void	calc_sidedist(t_wall *wall, t_info *info);
void	calc_dda(t_wall *wall, t_info *info);
void	calc_wall_tex(t_wall *wall, t_info *info);
void	select_wall_tex(t_wall *wall, t_info *info);
int		get_sprite_num(t_info *info, t_sprite *sp);
int		count_sprite(t_info *info);
void	get_sprite_info(t_info *info, t_sprite *sp);
void	get_sprite_pos(t_sprite *sp, t_info *info);
void	sort_sprite_dist(t_sprite *sp);
void	calc_sprite_info(t_info *info, t_sprite *sp);
void	calc_sprite_tex(t_sprite *sp, t_info *info, t_img *img);
void	padding(unsigned char **data, int start, int end);
int		init_bmp_header(t_bmp *bmp);
int		set_header_info(t_bmp *bmp);
int		set_bmp_data(t_info *info, t_bmp *bmp);
int		save(int cub_fd, t_info *info);

#endif
