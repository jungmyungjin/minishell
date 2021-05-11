/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 02:07:18 by ychoi             #+#    #+#             */
/*   Updated: 2021/01/01 03:59:05 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *p_src;
	size_t				i;

	i = 0;
	p_src = s;
	while (i < n)
	{
		if (*p_src == (unsigned char)c)
			return ((void *)p_src);
		p_src++;
		i++;
	}
	return (NULL);
}
