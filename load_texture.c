/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:24:31 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:24:32 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(t_info *info, t_map *map)
{
	int	i;
	int	r;

	info->tex = malloc(sizeof(int *) * 5);
	if (info->tex == NULL)
		return (-1);
	i = 0;
	while (i < 5)
	{
		info->img.texnum = i;
		r = load_image(info, &(info->tex[i]), map->t_path[i], &(info->img));
		if (r == -1)
			return (free_int_arr(&(info->tex), 0, i));
		i++;
	}
	info->img.img = mlx_new_image(info->mlx, info->s_w, info->s_h);
	if (info->img.img == NULL)
		return (-1);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, \
			&(info->img.bpp), &(info->img.l_s), &(info->img.e));
	if (info->img.data == NULL)
		return (-1);
	return (0);
}

int	load_image(t_info *info, int **tex, char *path, t_img *im)
{
	int	n;

	n = im->texnum;
	im->img = mlx_xpm_file_to_image(info->mlx, path, &(im->w[n]), &(im->h[n]));
	if (im->img == NULL)
		return (-1);
	im->r_w[n] = im->w[n] + (im->w[n] % 4);
	im->data = (int *)mlx_get_data_addr(im->img, &im->bpp, &im->l_s, &im->e);
	if (info->img.data == NULL)
		return (-1);
	*tex = malloc(sizeof(int) * (im->h[n] * im->r_w[n]));
	if (*tex == NULL)
		return (-1);
	copy_texture_color(im, tex, n);
	mlx_destroy_image(info->mlx, im->img);
	im->img = NULL;
	return (0);
}

void	copy_texture_color(t_img *img, int **tex, int num)
{
	int	x;
	int	y;
	int	rev_x;

	y = 0;
	while (y < img->h[num])
	{
		x = 0;
		while (x < img->w[num])
		{
			rev_x = (img->w[num] - x - 1);
			(*tex)[img->r_w[num] * y + rev_x] = img->data[img->w[num] * y + x];
			x++;
		}
		while (x < img->r_w[num])
		{
			(*tex)[img->r_w[num] * y + x] = 0;
			x++;
		}
		y++;
	}
}

int	allocate_buf_area(t_info *info)
{
	int	i;

	info->buf = malloc(sizeof(int *) * info->s_h);
	if (info->buf == NULL)
		return (-1);
	i = 0;
	while (i < info->s_h)
	{
		info->buf[i] = malloc(sizeof(int) * info->s_w);
		if (info->buf[i] == NULL)
			return (free_int_arr(&(info->buf), 0, i));
		i++;
	}
	info->zbuf = malloc(sizeof(double) * info->s_w + 1);
	if (info->zbuf == NULL)
		return (free_int_arr(&(info->buf), 0, i));
	return (0);
}
