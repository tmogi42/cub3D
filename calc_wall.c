/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:33:15 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 14:33:16 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_casting(t_info *info)
{
	int		x;
	t_wall	wall;

	draw_floor_and_ceiling(info);
	x = 0;
	while (x < info->s_w)
	{
		wall.camerax = 2 * x / (double)info->s_w - 1;
		wall.rdirx = info->dirx + info->cp_x * wall.camerax;
		wall.rdiry = info->diry + info->cp_y * wall.camerax;
		wall.mapx = (int)info->posx;
		wall.mapy = (int)info->posy;
		wall.deltadistx = fabs(1 / wall.rdirx);
		wall.deltadisty = fabs(1 / wall.rdiry);
		wall.hit = 0;
		calc_sidedist(&wall, info);
		calc_dda(&wall, info);
		calc_wall_tex(&wall, info);
		draw_wall(&wall, info, x);
		info->zbuf[x] = wall.perp;
		x++;
	}
	get_sprite_info(info, &(info->sp));
	sort_sprite_dist(&(info->sp));
	calc_sprite_info(info, &(info->sp));
}

void	calc_sidedist(t_wall *wall, t_info *info)
{
	if (wall->rdirx < 0)
	{
		wall->stepx = -1;
		wall->sidedistx = (info->posx - wall->mapx) * wall->deltadistx;
	}
	else
	{
		wall->stepx = 1;
		wall->sidedistx = (wall->mapx + 1.0 - info->posx) * wall->deltadistx;
	}
	if (wall->rdiry < 0)
	{
		wall->stepy = -1;
		wall->sidedisty = (info->posy - wall->mapy) * wall->deltadisty;
	}
	else
	{
		wall->stepy = 1;
		wall->sidedisty = (wall->mapy + 1.0 - info->posy) * wall->deltadisty;
	}
}

void	calc_dda(t_wall *wall, t_info *info)
{
	while (wall->hit == 0)
	{
		if (wall->sidedistx < wall->sidedisty)
		{			
			wall->sidedistx += wall->deltadistx;
			wall->mapx += wall->stepx;
			wall->side = 0;
		}
		else
		{
			wall->sidedisty += wall->deltadisty;
			wall->mapy += wall->stepy;
			wall->side = 1;
		}
		if (info->map.map[wall->mapy][wall->mapx] == '1')
			wall->hit = 1;
	}
}

void	calc_wall_tex(t_wall *wall, t_info *info)
{
	double	xdist;
	double	ydist;

	xdist = wall->mapx - info->posx + (1 - wall->stepx) / 2;
	ydist = wall->mapy - info->posy + (1 - wall->stepy) / 2;
	select_wall_tex(wall, info);
	if (wall->side == 0)
		wall->perp = xdist / wall->rdirx;
	else
		wall->perp = ydist / wall->rdiry;
	if (wall->perp <= 0.001)
		wall->perp = 0.001;
	wall->l_height = (int)(info->s_h / wall->perp);
	wall->draw_s = -wall->l_height / 2 + info->s_h / 2;
	if (wall->draw_s < 0)
		wall->draw_s = 0;
	wall->draw_e = wall->l_height / 2 + info->s_h / 2;
	if (wall->draw_e >= info->s_h)
		wall->draw_e = info->s_h - 1;
	if (wall->side == 0)
		wall->wallx = info->posy + wall->perp * wall->rdiry;
	else
		wall->wallx = info->posx + wall->perp * wall->rdirx;
	wall->wallx -= floor(wall->wallx);
}

void	select_wall_tex(t_wall *wall, t_info *info)
{
	if (wall->rdiry >= 0 && wall->side == 1)
		info->img.texnum = 0;
	else if (wall->rdiry < 0 && wall->side == 1)
		info->img.texnum = 1;
	else if (wall->rdirx >= 0 && wall->side == 0)
		info->img.texnum = 2;
	else if (wall->rdirx < 0 && wall->side == 0)
		info->img.texnum = 3;
}
