/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:28:07 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:28:09 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strcpy(char *src, char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		src[i] = s[i];
		i++;
	}
	src[i] = '\0';
	return (i);
}

static int	count_strs(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	size(const char *s, char c)
{
	int	i;

	i = 1;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**my_free(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		n;
	char	**new_strs;

	n = 0;
	if (s == NULL)
		return (NULL);
	new_strs = (char **)malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (new_strs == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			new_strs[n] = (char *)malloc(sizeof(char) * (size(s, c) + 1));
			if (new_strs[n] == 0)
				return (my_free(new_strs, n));
			s += my_strcpy(new_strs[n], c, s);
			n++;
		}
		else
			s++;
	}
	new_strs[n] = NULL;
	return (new_strs);
}
