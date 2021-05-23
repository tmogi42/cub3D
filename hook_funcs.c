/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:33:39 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 14:33:39 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_update(t_info *info)
{
	if (info->key_w)
		move_player(info, 0, 1);
	if (info->key_s)
		move_player(info, 0, -1);
	if (info->key_d)
		move_player(info, 1, 1);
	if (info->key_a)
		move_player(info, 1, -1);
	if (info->key_ar_r)
		rotate_player(info, 1);
	if (info->key_ar_l)
		rotate_player(info, -1);
}

int	key_press(int key, t_info *info)
{
	if (key == 65307)
		safe_shutdown(info);
	else if (key == 119)
		info->key_w = 1;
	else if (key == 97)
		info->key_a = 1;
	else if (key == 115)
		info->key_s = 1;
	else if (key == 100)
		info->key_d = 1;
	else if (key == 65361)
		info->key_ar_l = 1;
	else if (key == 65363)
		info->key_ar_r = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == 119)
		info->key_w = 0;
	else if (key == 97)
		info->key_a = 0;
	else if (key == 115)
		info->key_s = 0;
	else if (key == 100)
		info->key_d = 0;
	else if (key == 65361)
		info->key_ar_l = 0;
	else if (key == 65363)
		info->key_ar_r = 0;
	return (0);
}

int	safe_shutdown(t_info *info)
{
	clear_all_params(info);
	exit(0);
	return (0);
}
