/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 21:27:54 by mjung             #+#    #+#             */
/*   Updated: 2021/04/21 21:39:26 by jungmyungjin     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	int	index;
	int	is_found;

	index = 0;
	is_found = 0;
	while ((unsigned long)index < len)
	{
		if (((char *)b)[index] == c)
		{
			is_found = 1;
			break ;
		}
		index++;
	}
	if (is_found)
		return (&((char *)b)[index]);
	else
		return (NULL);
}
