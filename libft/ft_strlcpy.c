/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:51:35 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/07 09:00:08 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	n;
	unsigned int	i;

	if (src == NULL)
		return (0);
	i = 0;
	n = ft_strlen(src);
	if (size == 0)
		return (n);
	while (i < size - 1)
	{
		if (src[i] == '\0')
			break ;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (n);
}
