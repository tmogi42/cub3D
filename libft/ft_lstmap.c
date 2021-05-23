/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmogi <dmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:00:05 by dmogi             #+#    #+#             */
/*   Updated: 2021/04/16 15:25:32 by dmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;
	t_list	*ele;

	new_list = NULL;
	while (lst != NULL)
	{
		ele = ft_lstnew(f(lst->content));
		if (ele == NULL)
		{
			while (new_list != NULL)
			{
				tmp = new_list;
				del(new_list->content);
				new_list = new_list->next;
				free(tmp);
			}
			return (NULL);
		}
		ft_lstadd_back(&new_list, ele);
		lst = lst->next;
	}
	return (new_list);
}
