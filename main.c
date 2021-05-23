/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:33:48 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 14:33:49 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_info *info, int lr_flag, int p_or_m)
{
	double	dirx;
	double	diry;
	int		dest_x;
	int		dest_y;

	dirx = info->dirx;
	diry = info->diry;
	if (lr_flag == 1)
	{
		dirx = -(info->diry);
		diry = info->dirx;
	}
	dest_x = (int)(info->posx + p_or_m * (dirx * info->movespeed));
	dest_y = (int)(info->posy + p_or_m * (diry * info->movespeed));
	if (info->map.map[(int)info->posy][dest_x] != '1')
		info->posx += p_or_m * (dirx * info->movespeed);
	if (info->map.map[dest_y][(int)(info->posx)] != '1')
		info->posy += p_or_m * (diry * info->movespeed);
}

void	rotate_player(t_info *info, int p_or_m)
{
	double	old_dirx;
	double	old_planex;
	double	r_angle;

	r_angle = p_or_m * info->rotspeed;
	old_dirx = info->dirx;
	old_planex = info->cp_x;
	info->dirx = info->dirx * cos(r_angle) - info->diry * sin(r_angle);
	info->diry = old_dirx * sin(r_angle) + info->diry * cos(r_angle);
	info->cp_x = info->cp_x * cos(r_angle) - info->cp_y * sin(r_angle);
	info->cp_y = old_planex * sin(r_angle) + info->cp_y * cos(r_angle);
}

int	main_loop(t_info *info)
{
	calc_casting(info);
	draw_image(info, &(info->img));
	key_update(info);
	return (0);
}

int	start_game(t_info *info)
{
	if (allocate_buf_area(info) == -1)
		return (-1);
	info->win = mlx_new_window(info->mlx, info->s_w, info->s_h, "cub3d");
	if (info->win == NULL)
		return (-1);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, 2, 1L << 0, &key_press, info);
	mlx_hook(info->win, 3, 1L << 1, &key_release, info);
	mlx_hook(info->win, 17, 1L << 17, &safe_shutdown, info);
	mlx_loop(info->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_info	info;

	fd = judge_input_args(argc, argv);
	if (fd == -1)
		return (error(fd, -1, NULL));
	if (init_params(&info) == -1)
		return (error(fd, -2, NULL));
	if (read_cub_file(fd, &info) == -1)
		return (error(fd, -3, &info));
	if (check_read_data(&info) == -1)
		return (error(fd, -3, &info));
	if (load_texture(&info, &(info.map)) == -1)
		return (error(fd, -4, &info));
	if (argc == 2)
	{
		if (start_game(&info) == -1)
			return (error(fd, -5, &info));
	}
	if (save(fd, &info) == -1)
		return (error(fd, -6, &info));
	return (0);
}
