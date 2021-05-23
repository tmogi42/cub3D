/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:24:11 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:24:11 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	gnl_strjoin(char **line, char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	lsize;
	char	*save_line;

	lsize = gnl_strlen(*line);
	save_line = gnl_strdup(line, 0);
	if (save_line == NULL)
		return (-1);
	*line = malloc(sizeof(char) * (lsize + n + 1));
	if (line == NULL)
		return (free_all(&save_line, NULL, NULL, -1));
	i = -1;
	while (++i < lsize)
		(*line)[i] = save_line[i];
	free(save_line);
	j = -1;
	while (++j < n)
		(*line)[i + j] = src[j];
	(*line)[i + j] = '\0';
	return (1);
}

char	*gnl_strdup(char **src, size_t nextl_p)
{
	size_t	i;
	size_t	new_size;
	char	*new;

	i = 0;
	new_size = gnl_strlen(&(*src)[nextl_p]);
	new = malloc(sizeof(char) * (new_size + 1));
	if (new == NULL)
		return (NULL);
	if ((*src)[nextl_p] != '\0')
	{
		while (i < new_size)
		{
			new[i] = (*src)[nextl_p + i];
			i++;
		}
	}
	new[i] = '\0';
	free(*src);
	return (new);
}
