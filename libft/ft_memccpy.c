/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:29:04 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:29:05 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t		i;
	char		*p_dest;
	char		*p_src;
	char		ch_c;

	i = 0;
	p_dest = (char *)dest;
	p_src = (char *)src;
	ch_c = (char)c;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		if (p_dest[i] == ch_c)
			return (&p_dest[i] + 1);
		i++;
	}
	return (NULL);
}
