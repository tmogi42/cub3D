/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:27:37 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 13:56:20 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_num(char *p, long i, int count, int n)
{
	if (n < 0)
	{
		p[0] = '-';
		i *= -1;
	}
	if (i == 0)
	{
		p[0] = '0';
		p[1] = '\0';
		return ;
	}
	p[count--] = '\0';
	while (i != 0)
	{
		p[count--] = i % 10 + '0';
		i /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	i;
	int		count;
	char	*p;

	i = n;
	count = 0;
	if (i == 0)
		count = 1;
	if (n < 0)
		count++;
	while (i != 0)
	{
		count++;
		i /= 10;
	}
	p = (char *)malloc(sizeof(char) * (count + 1));
	if (p == NULL)
		return (NULL);
	i = n;
	set_num(p, i, count, n);
	p[count] = '\0';
	return (p);
}
