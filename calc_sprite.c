/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:33:10 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 14:33:11 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sprite_info(t_info *info, t_sprite *sp)
{
	int	i;

	i = 0;
	get_sprite_pos(sp, info);
	while (i < sp->num)
	{
		sp->distx = (info->posx - sp->x[i]) * (info->posx - sp->x[i]);
		sp->disty = (info->posy - sp->y[i]) * (info->posy - sp->y[i]);
		sp->order[i] = i;
		sp->dist[i++] = sp->distx + sp->disty;
	}
}

void	get_sprite_pos(t_sprite *sp, t_info *info)
{
	int		i;
	int		j;
	int		num;

	i = 0;
	num = 0;
	while (i < info->map.height)
	{
		j = 0;
		while (j < my_strlen(info->map.map[i]))
		{
			if (info->map.map[i][j] == '2')
			{
				sp->x[num] = j + 0.5;
				sp->y[num] = i + 0.5;
				num++;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprite_dist(t_sprite *sp)
{
	int		i;
	int		j;
	double	tmp;
	int		tmp_n;

	i = 0;
	while (i < sp->num)
	{
		j = 0;
		while (j < sp->num - 1)
		{
			if (sp->dist[j] < sp->dist[j + 1])
			{
				tmp = sp->dist[j];
				tmp_n = sp->order[j];
				sp->dist[j] = sp->dist[j + 1];
				sp->order[j] = sp->order[j + 1];
				sp->dist[j + 1] = tmp;
				sp->order[j + 1] = tmp_n;
			}
			j++;
		}
		i++;
	}
}

void	calc_sprite_info(t_info *info, t_sprite *sp)
{
	int	i;

	i = 0;
	sp->inv_d = 1.0 / (info->cp_x * info->diry - info->dirx * info->cp_y);
	while (i < sp->num)
	{
		sp->sp_x = sp->x[sp->order[i]] - info->posx;
		sp->sp_y = sp->y[sp->order[i]] - info->posy;
		sp->tf_x = sp->inv_d * (info->diry * sp->sp_x - info->dirx * sp->sp_y);
		sp->tf_y = sp->inv_d * (-info->cp_y * sp->sp_x + info->cp_x * sp->sp_y);
		sp->s_x = (int)((info->s_w / 2) * (1 + sp->tf_x / sp->tf_y));
		sp->height = (int)fabs((info->s_h / sp->tf_y));
		sp->draw_sy = -sp->height / 2 + info->s_h / 2;
		if (sp->draw_sy < 0)
			sp->draw_sy = 0;
		sp->draw_ey = sp->height / 2 + info->s_h / 2;
		if (sp->draw_ey >= info->s_h)
			sp->draw_ey = info->s_h - 1;
		calc_sprite_tex(sp, info, &(info->img));
		i++;
	}
}

void	calc_sprite_tex(t_sprite *sp, t_info *info, t_img *img)
{
	int	x;
	int	sp_cpx_pixel;

	sp->width = (int)fabs((info->s_w / sp->tf_y));
	sp->draw_sx = -sp->width / 2 + sp->s_x;
	if (sp->draw_sx < 0)
		sp->draw_sx = 0;
	sp->draw_ex = sp->width / 2 + sp->s_x;
	if (sp->draw_ex >= info->s_w)
		sp->draw_ex = info->s_w - 1;
	x = sp->draw_sx;
	while (x < sp->draw_ex)
	{
		sp_cpx_pixel = (x - (-sp->width / 2 + sp->s_x));
		sp->texx = (int)(sp_cpx_pixel * img->w[4] / sp->width);
		if (sp->texx < 0)
			sp->texx = 0;
		if (sp->tf_y > 0 && x > 0 && x < info->s_w && sp->tf_y < info->zbuf[x])
			draw_sprite(info, sp, img, x);
		x++;
	}
}
