/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:35:57 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/07 08:59:34 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	nd;
	size_t	ns;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	nd = ft_strlen(dest);
	ns = ft_strlen(src);
	if (size <= nd)
		return (ns + size);
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < size - nd - 1)
		dest[i++] = src[j++];
	dest[i] = '\0';
	if (size >= nd)
		return (nd + ns);
	else
		return (ns + size);
}
