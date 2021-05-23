/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:33:41 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 14:33:42 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_params(t_info *info)
{
	init_map_data(info);
	init_info_data(info);
	info->mlx = mlx_init();
	if (info->mlx == NULL)
		return (-1);
	mlx_get_screen_size(info->mlx, &(info->s_w), &(info->s_h));
	return (0);
}

void	init_map_data(t_info *info)
{
	info->mlx = NULL;
	info->win = NULL;
	info->map.res[0] = 0;
	info->bmp.width = 0;
	info->bmp.height = 0;
	info->map.res[1] = 0;
	info->map.t_path[0] = NULL;
	info->map.t_path[1] = NULL;
	info->map.t_path[2] = NULL;
	info->map.t_path[3] = NULL;
	info->map.t_path[4] = NULL;
	info->map.rgb[0] = -1;
	info->map.rgb[1] = -1;
	info->map.rgb[2] = -1;
	info->map.f_color = -1;
	info->map.c_color = -1;
	info->map.max_width = 0;
	info->map.height = 0;
	info->map.tmpmap = NULL;
	info->map.map = NULL;
}

void	init_info_data(t_info *info)
{
	info->posx = -1.0;
	info->posy = -1.0;
	info->dirx = 0;
	info->diry = 0;
	info->cp_x = 0;
	info->cp_y = 0;
	info->movespeed = 0.033;
	info->rotspeed = 0.01;
	info->key_w = 0;
	info->key_a = 0;
	info->key_s = 0;
	info->key_d = 0;
	info->key_esc = 0;
	info->key_ar_l = 0;
	info->key_ar_r = 0;
	info->zbuf = NULL;
	info->buf = NULL;
	info->tex = NULL;
	info->sp.x = NULL;
	info->sp.y = NULL;
	info->sp.order = NULL;
	info->sp.dist = NULL;
	info->img.img = NULL;
	info->img.data = NULL;
}

char	set_player_pos(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->map.height)
	{
		j = 0;
		while (j < my_strlen(info->map.map[i]))
		{
			if (my_chrstr(info->map.map[i][j], "EWSN") == 1)
			{
				if (info->posx != -1.0 || info->posy != -1.0)
					return (0);
				info->posx = (double)j + 0.5;
				info->posy = (double)i + 0.5;
			}
			else if (my_chrstr(info->map.map[i][j], "012 ") == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (info->posx == -1 || info->posx == -1)
		return (0);
	return (info->map.map[(int)info->posy][(int)info->posx]);
}

void	set_player_dir(char p_dir, t_info *info)
{
	if (p_dir == 'N')
	{
		info->diry = -1.0;
		info->cp_x = 1.0;
	}
	if (p_dir == 'S')
	{
		info->diry = 1.0;
		info->cp_x = -1.0;
	}
	if (p_dir == 'E')
	{
		info->dirx = 1.0;
		info->cp_y = 1.0;
	}
	if (p_dir == 'W')
	{
		info->dirx = -1.0;
		info->cp_y = -1.0;
	}	
}
