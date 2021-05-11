/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:54:43 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/09 00:21:46 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*cur;

	head = NULL;
	while (lst != NULL)
	{
		if (head == NULL)
		{
			head = ft_lstnew((*f)(lst->content));
			cur = head;
		}
		else
		{
			cur->next = ft_lstnew((*f)(lst->content));
			cur = cur->next;
		}
		if (cur == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (head);
}
