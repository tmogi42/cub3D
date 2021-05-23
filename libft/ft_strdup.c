/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 20:11:30 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 10:11:24 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	n;
	size_t	i;
	char	*p;

	i = 0;
	n = ft_strlen(src);
	p = (char *)malloc(sizeof(char) * (n + 1));
	if (p == NULL)
		return (NULL);
	while (i < n)
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
