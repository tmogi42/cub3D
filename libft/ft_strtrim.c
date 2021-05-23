/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:58:13 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 11:41:55 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	search_set(char const *s1, char const *set, int *s, int *e)
{
	unsigned int	n;
	unsigned int	i;

	i = 0;
	n = ft_strlen(s1);
	while (is_set(s1[i], set) != 0)
	{
		i++;
		if (s1[i] == '\0')
			return (-1);
	}
	*s = i;
	i = n - 1;
	while (is_set(s1[i], set) != 0)
		i--;
	*e = i;
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s;
	int		e;
	int		i;
	char	*p;

	if (s1 == NULL)
		return (NULL);
	if (s1[0] == '\0' || set[0] == '\0')
	{
		p = ft_strdup(s1);
		return (p);
	}
	if (search_set(s1, set, &s, &e) == -1)
		return (malloc(sizeof(char)));
	p = (char *)malloc(sizeof(char) * (e - s + 2));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s <= e)
		p[i++] = s1[s++];
	p[i] = '\0';
	return (p);
}
