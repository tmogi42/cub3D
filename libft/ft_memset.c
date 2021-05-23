/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:35:07 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/03 13:37:59 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*t;

	t = (unsigned char *)b;
	i = 0;
	while (i < n)
	{
		t[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
