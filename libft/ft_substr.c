/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:17:27 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 10:34:12 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	n;
	unsigned int	i;
	char			*p;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= start)
		return ((char *)malloc(sizeof(char)));
	if (len > ft_strlen(s))
		n = ft_strlen(s);
	else
		n = len;
	p = (char *)malloc(sizeof(char) * (n + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < n)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
