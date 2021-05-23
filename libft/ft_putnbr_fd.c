/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:44:48 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 14:04:15 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	s;
	char			c;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		write(fd, "-", 1);
		s = (unsigned int)(n * -1);
	}
	else
		s = (unsigned int)n;
	if (s >= 10)
		ft_putnbr_fd(s / 10, fd);
	c = '0' + s % 10;
	ft_putchar_fd(c, fd);
}
