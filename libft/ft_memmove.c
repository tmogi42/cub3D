/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:49:18 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/03 23:14:44 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	if (dst == NULL && src == NULL)
		return (dst);
	ptr = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	i = 0;
	if (ptr2 < ptr)
		while (++i <= len)
			ptr[len - i] = ptr2[len - i];
	else
		while (len-- > 0)
			*(ptr++) = *(ptr2++);
	return (dst);
}
