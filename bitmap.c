/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:33:01 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 14:33:06 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save(int cub_fd, t_info *info)
{
	if (init_bmp_header(&(info->bmp)) == -1)
		return (-1);
	info->s_w = info->bmp.width;
	info->s_h = info->bmp.height;
	if (allocate_buf_area(info) == -1)
	{
		free(info->bmp.rgb);
		return (-1);
	}
	calc_casting(info);
	if (set_bmp_data(info, &(info->bmp)) == -1)
	{
		free(info->bmp.rgb);
		return (-1);
	}
	clear_all_params(info);
	close(cub_fd);
	return (0);
}

int	init_bmp_header(t_bmp *bmp)
{
	unsigned long	width;
	unsigned long	height;

	width = bmp->width;
	height = bmp->height;
	bmp->filesize = (width * height * 3) + 54;
	bmp->offset = 54;
	bmp->header_size = 40;
	bmp->width = width;
	bmp->height = height;
	bmp->planes = 1;
	bmp->color = 24;
	bmp->data_size = width * height;
	bmp->no_val = 0;
	bmp->real_width = (width * 3) + width % 4;
	bmp->rgb = malloc(sizeof(unsigned char) * bmp->real_width);
	if (bmp->rgb == NULL)
		return (-1);
	return (0);
}

int	set_bmp_data(t_info *info, t_bmp *bmp)
{
	int	i;
	int	j;

	i = 1;
	if (set_header_info(bmp) == -1)
		return (-1);
	while (i <= info->s_h)
	{
		j = 0;
		while (j < info->s_w)
		{
			bmp->rgb[j * 3] = info->buf[info->s_h - i][j] & 255;
			bmp->rgb[j * 3 + 1] = (info->buf[info->s_h - i][j] >> 8) & 255;
			bmp->rgb[j * 3 + 2] = (info->buf[info->s_h - i][j] >> 16) & 255;
			j++;
		}
		padding(&(bmp->rgb), bmp->width * 3, bmp->real_width);
		write(bmp->fd, bmp->rgb, bmp->real_width);
		i++;
	}
	free(bmp->rgb);
	return (0);
}

int	set_header_info(t_bmp *bmp)
{
	bmp->fd = open("./image.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (bmp->fd == -1)
		return (-1);
	write(bmp->fd, "BM", 2);
	write(bmp->fd, &(bmp->filesize), 4);
	write(bmp->fd, &(bmp->no_val), 4);
	write(bmp->fd, &(bmp->offset), 4);
	write(bmp->fd, &(bmp->header_size), 4);
	write(bmp->fd, &(bmp->width), 4);
	write(bmp->fd, &(bmp->height), 4);
	write(bmp->fd, &(bmp->planes), 2);
	write(bmp->fd, &(bmp->color), 2);
	write(bmp->fd, &(bmp->no_val), 4);
	write(bmp->fd, &(bmp->data_size), 4);
	write(bmp->fd, &(bmp->no_val), 4);
	write(bmp->fd, &(bmp->no_val), 4);
	write(bmp->fd, &(bmp->no_val), 4);
	write(bmp->fd, &(bmp->no_val), 4);
	return (0);
}

void	padding(unsigned char **data, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		(*data)[i] = 0;
		i++;
	}
}
