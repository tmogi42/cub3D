/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:04:41 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 13:26:54 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	n;
	unsigned int	i;
	char			*p;

	if (s == NULL || !f)
		return (NULL);
	n = ft_strlen(s);
	p = (char *)malloc(sizeof(char) * (n + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
