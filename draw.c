/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:33:26 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 14:33:27 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_info *info)
{
	int	x;
	int	y;

	y = info->s_h / 2;
	while (y < info->s_h)
	{
		x = 0;
		while (x < info->s_w)
		{
			info->buf[y][x] = info->map.f_color;
			info->buf[info->s_h - y - 1][x] = info->map.c_color;
			x++;
		}
		y++;
	}
}

void	draw_wall(t_wall *wall, t_info *info, int x)
{
	int		y;
	int		t_n;
	int		color;
	double	texpos;

	t_n = info->img.texnum;
	wall->texx = (int)(wall->wallx * (double)info->img.w[t_n]);
	if (wall->side == 0 && wall->rdirx > 0)
		wall->texx = info->img.w[t_n] - wall->texx - 1;
	if (wall->side == 1 && wall->rdiry < 0)
		wall->texx = info->img.w[t_n] - wall->texx - 1;
	wall->step = 1.0 * info->img.h[t_n] / wall->l_height;
	texpos = (wall->draw_s - info->s_h / 2 + wall->l_height / 2) * wall->step;
	y = wall->draw_s;
	while (y < wall->draw_e)
	{
		wall->texy = (int)texpos;
		if (wall->texy > (info->img.h[t_n] - 1))
			wall->texy = (info->img.h[t_n] - 1);
		texpos += wall->step;
		color = info->tex[t_n][info->img.r_w[t_n] * wall->texy + wall->texx];
		info->buf[y][x] = color;
		y++;
	}
}

void	draw_sprite(t_info *info, t_sprite *sp, t_img *img, int x)
{
	int	y;
	int	d;
	int	color;

	y = sp->draw_sy;
	while (y < sp->draw_ey)
	{
		d = y * 256 - info->s_h * 128 + sp->height * 128;
		sp->texy = ((d * img->h[4]) / sp->height) / 256;
		if (sp->texy < 0)
			sp->texy = 0;
		color = info->tex[4][img->w[4] * sp->texy + sp->texx];
		if ((color & 0x00FFFFFF) != 0)
			info->buf[y][x] = color;
		y++;
	}
}

void	draw_image(t_info *info, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < info->s_h)
	{
		x = 0;
		while (x < info->s_w)
		{
			img->data[y * info->s_w + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, img->img, 0, 0);
}
