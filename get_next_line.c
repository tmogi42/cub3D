/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:24:15 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:24:15 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	search_newline(char *buf, size_t *i)
{
	*i = 0;
	while (buf[*i] != '\0')
	{
		if (buf[*i] == '\n')
			return (1);
		(*i)++;
	}
	return (0);
}

int	get_line_from_tmp(char **line, char **tmp)
{
	size_t	i;
	int		newline_flag;

	i = 0;
	newline_flag = search_newline(*tmp, &i);
	if (gnl_strjoin(line, *tmp, i) == -1)
		return (free_all(line, NULL, tmp, -1));
	if (newline_flag == 1)
		i++;
	*tmp = gnl_strdup(tmp, i);
	if (tmp == NULL)
		return (free_all(line, NULL, tmp, -1));
	if ((*tmp)[0] == '\0')
		free_all(NULL, NULL, tmp, -1);
	return (newline_flag);
}

int	save_to_tmp(char **line, char **tmp, char **buf, int i)
{
	*tmp = gnl_strdup(buf, i);
	if (*tmp == NULL)
		return (free_all(line, buf, NULL, -1));
	if ((*tmp)[0] == '\0')
		free_all(NULL, NULL, tmp, 0);
	return (0);
}	

int	gnl_read(int fd, char **line, char **tmp, int *newline_flag)
{
	size_t	i;
	ssize_t	rdsize;
	char	*buf;

	while (*newline_flag != 1)
	{
		buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (buf == NULL)
			return (free_all(line, NULL, NULL, -1));
		rdsize = read(fd, buf, (size_t)BUFFER_SIZE);
		if (rdsize == -1)
			return (free_all(line, &buf, NULL, -1));
		buf[rdsize] = '\0';
		if (rdsize == 0)
			return (free_all(NULL, &buf, NULL, 0));
		*newline_flag = search_newline(buf, &i);
		if ((gnl_strjoin(line, buf, i)) == -1)
			return (free_all(line, &buf, NULL, -1));
		if (*newline_flag == 1)
			i++;
		if (save_to_tmp(line, tmp, &buf, i) == -1)
			return (-1);
	}
	return (1);
}

int	get_next_line(int fd, char **line, char **tmp)
{
	int	is_finish;
	int	newline_flag;

	newline_flag = 0;
	*line = malloc(sizeof(char) * 1);
	if (line == NULL)
		return (free_all(NULL, NULL, tmp, -1));
	(*line)[0] = '\0';
	if (*tmp)
	{
		is_finish = get_line_from_tmp(line, tmp);
		if (is_finish == -1)
			return (-1);
		if (is_finish == 1)
			return (1);
	}
	return (gnl_read(fd, line, tmp, &newline_flag));
}
