/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:39:20 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:38 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!(*lst))
		return ;
	else
	{
		ft_lstclear(&(*lst)->next, (void *)del);
		del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
