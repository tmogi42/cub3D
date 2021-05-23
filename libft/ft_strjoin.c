/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:42:53 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 10:57:07 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;
	char			*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	n = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (n + 1));
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}
