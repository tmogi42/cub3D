/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:57:29 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/07 17:56:04 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, unsigned int l)
{
	unsigned int	s;

	if (n[0] == '\0')
		return ((char *)h);
	s = ft_strlen(n);
	while (*h != '\0' && l >= s)
	{
		if (*h == *n)
			if (ft_memcmp(h, n, s) == 0)
				return ((char *)h);
		h++;
		l--;
	}
	return (NULL);
}
