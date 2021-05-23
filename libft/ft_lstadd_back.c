/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:46:52 by tmogi             #+#    #+#             */
/*   Updated: 2020/11/08 14:58:27 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || (*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	if (lst != NULL && (*lst) != NULL && new != NULL)
	{
		last = (*lst);
		if (last == NULL)
		{
			(*lst) = new;
			return ;
		}
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
