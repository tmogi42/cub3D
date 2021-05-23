/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free_libs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:24:43 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:24:44 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_all(char **line, char **buf, char **tmp, int result)
{
	if (line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	if (buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	if (tmp != NULL)
	{
		free(*tmp);
		*tmp = NULL;
	}
	return (result);
}

int	free_int_arr(int ***arr, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
	return (-1);
}

int	free_char_arr(char ***arr, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
	return (-1);
}

int	free_members(t_info *info)
{
	int	i;

	i = 0;
	while (i < 5)
		free(info->map.t_path[i++]);
	if (info->map.map != NULL)
		free_char_arr(&(info->map.map), 0, info->map.height);
	free(info->sp.x);
	free(info->sp.y);
	free(info->sp.order);
	free(info->sp.dist);
	return (0);
}

void	clear_all_params(t_info *info)
{
	int	i;

	i = 0;
	free_members(info);
	if (info->buf != NULL)
	{
		while (i < info->s_h)
			free(info->buf[i++]);
	}
	free(info->buf);
	free(info->zbuf);
	i = 0;
	if (info->tex != NULL)
	{
		while (i < 5)
			free(info->tex[i++]);
	}
	free(info->tex);
	if (info->img.img != NULL)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->win != NULL)
		mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
}
